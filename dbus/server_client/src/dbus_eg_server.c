#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dbus/dbus.h>

#if 0
#include <dbus/dbus-glib-lowlevel.h>
GMainLoop *mainloop;
#endif

#define NAME_BUS        "com.igsong.dbus"
#define NAME_OBJECT     "com/igsong/dbus"
#define NAME_INTERFACE  "com.igsong.dbus.Interface"

const char *server_introspection_xml =
    DBUS_INTROSPECT_1_0_XML_DOCTYPE_DECL_NODE
    "<node>\n"
    "  <interface name='"NAME_BUS".Introspectable'>\n"
    "    <method name='Introspect'>\n"
    "      <arg name='data' type='s' direction='out' />\n"
    "    </method>\n"
    "  </interface>\n"
    "  <interface name='"NAME_BUS".Properties'>/n"
    "    <method name='Get'>\n"
    "      <arg name='interface' type='s' direction='in' />\n"
    "      <arg name='property' type='s' direction='in' />\n"
    "      <arg name='value' type='s' direction='out' />\n"
    "    </method>\n"
    "    <method name='GetAll'>\n"
    "      <arg name='interface' type='s' direction='in' />\n"
    "      <arg name='properties' type='a{sv}' direction='out' />\n"
    "    </method>\n"
    "  </interface>\n"
    "  <interface name='"NAME_BUS".Properties'>\n"
    "    <method name='Hello'>\n"
    "      <arg name='say' type='s' direction='in' />\n"
    "      <arg type='s' direction='out' />\n"
    "    </method>\n"
    "  </interface>\n"
    "</node>\n";

DBusHandlerResult server_get_property_handler(
        DBusConnection *connection, const char *property,  DBusMessage *reply)
{
    DBusHandlerResult result = DBUS_HANDLER_RESULT_HANDLED;

    if (!strcmp(property, "Bus")) {
        const char *str = NAME_BUS;
        dbus_message_append_args(reply, DBUS_TYPE_STRING, &str, DBUS_TYPE_INVALID);
    } else if (!strcmp(property, "Object")) {
        const char *str = NAME_OBJECT;
        dbus_message_append_args(reply, DBUS_TYPE_STRING, &str, DBUS_TYPE_INVALID);
    } else {
        result = DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
    }

    return result;
}

DBusHandlerResult server_get_all_properties_handler(
        DBusConnection *connection, DBusMessage *reply)
{
    DBusHandlerResult result = DBUS_HANDLER_RESULT_HANDLED;
    DBusMessageIter array, dict, iter, variant;
    const char *bus = "Bus";
    const char *bus_var = NAME_BUS;
    const char *object = "Object";
    const char *object_var = NAME_OBJECT;

    dbus_message_iter_init_append(reply, &iter);
    dbus_message_iter_open_container(&iter, DBUS_TYPE_ARRAY, "${sv}", &array);

    dbus_message_iter_open_container(&iter, DBUS_TYPE_DICT_ENTRY, NULL, &dict);
    dbus_message_iter_append_basic(&dict, DBUS_TYPE_STRING, &bus);
    dbus_message_iter_open_container(&dict, DBUS_TYPE_VARIANT, "s", &variant);
    dbus_message_iter_append_basic(&variant, DBUS_TYPE_STRING, &bus_var);
    dbus_message_iter_close_container(&dict, &variant);
    dbus_message_iter_close_container(&array, &dict);

    dbus_message_iter_open_container(&iter, DBUS_TYPE_DICT_ENTRY, NULL, &dict);
    dbus_message_iter_append_basic(&dict, DBUS_TYPE_STRING, &object);
    dbus_message_iter_open_container(&dict, DBUS_TYPE_VARIANT, "s", &variant);
    dbus_message_iter_append_basic(&variant, DBUS_TYPE_STRING, &object_var);
    dbus_message_iter_close_container(&dict, &variant);
    dbus_message_iter_close_container(&array, &dict);

    dbus_message_iter_close_container(&iter, &array);

    return result;
}

DBusHandlerResult server_message_handler(DBusConnection *connection,
        DBusMessage *message, void *data) {
    DBusHandlerResult result = DBUS_HANDLER_RESULT_HANDLED;
    DBusMessage *reply = NULL;
    DBusError error;

    printf("got dbus request : %s.%s on %s\n",
            dbus_message_get_interface(message),
            dbus_message_get_member(message),
            dbus_message_get_path(message));

    dbus_error_init(&error);

    if (dbus_message_is_method_call(message, DBUS_INTERFACE_INTROSPECTABLE, "Introspect")) {
        if (!(reply = dbus_message_new_method_return(message)))
            goto fail;

        dbus_message_append_args(reply, DBUS_TYPE_STRING, &server_introspection_xml, DBUS_TYPE_INVALID);
    } else if (dbus_message_is_method_call(message, DBUS_INTERFACE_PROPERTIES, "Get")) {
        const char *interface, *property;

        if (!dbus_message_get_args(message, &error, DBUS_TYPE_STRING, &interface,
                    DBUS_TYPE_STRING, &property, DBUS_TYPE_INVALID));
                goto fail;

        if (!(reply = dbus_message_new_method_return(message)))
            goto fail;

        result = server_get_property_handler(connection, property, reply);
    } else if (dbus_message_is_method_call(message, DBUS_INTERFACE_PROPERTIES, "GetAll")) {
        if (!(reply = dbus_message_new_method_return(message)))
            goto fail;

        result = server_get_all_properties_handler(connection, reply);
    } else if (dbus_message_is_method_call(message, NAME_INTERFACE, "Hello")) {
        const char *answer = "Bye";

        if (!(reply = dbus_message_new_method_return(message)))
            goto fail;

        dbus_message_append_args(reply, DBUS_TYPE_STRING, &answer, DBUS_TYPE_INVALID);
    } else {
        return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
    }

fail:
    if (dbus_error_is_set(&error)) {
        if (reply)
            dbus_message_unref(reply);
        reply = dbus_message_new_error(message, error.name, error.message);
        dbus_error_free(&error);
    }

    if (!reply)
        return DBUS_HANDLER_RESULT_NEED_MEMORY;

    if (!dbus_connection_send(connection, reply, NULL))
        result = DBUS_HANDLER_RESULT_NEED_MEMORY;
    dbus_message_unref(reply);

    return result;
}

const DBusObjectPathVTable server_vtable = {
    .message_function = server_message_handler
};

void dbus_eg_server_release(DBusConnection *connection)
{
    if (NULL != connection) {
        dbus_connection_unref(connection);
    }
}

DBusConnection *dbus_eg_server_initialize(void)
{
    DBusError error;
    DBusConnection *connection = NULL;
    int result = 0;

    dbus_error_init(&error);
    connection = dbus_bus_get(DBUS_BUS_SESSION, &error);
    if (dbus_error_is_set(&error)) {
        fprintf(stderr, "dbus_error_init() failed, %s\n", error.message);
        goto fail;
    }
    printf("connected to %s\n", dbus_connection_get_server_id(connection));

    result = dbus_bus_request_name(connection, NAME_BUS,
            DBUS_NAME_FLAG_REPLACE_EXISTING, &error);
    if (DBUS_REQUEST_NAME_REPLY_PRIMARY_OWNER != result) {
        fprintf(stderr, "dbus_bus_request_name() failed, %s\n", error.message);
        goto fail;
    }

    if (!dbus_connection_register_object_path(connection, NAME_OBJECT, &server_vtable, NULL)) {
        fprintf(stderr, "dbus_connection_register_object_path() failed, %s\n", error.message);
        goto fail;
    }

    return connection;

fail:
    dbus_error_free(&error);
    dbus_eg_server_release(connection);
    return NULL;
}

int main(int argc, char argv[])
{
    printf("hello, this is a server.\n");

    DBusConnection *connection = dbus_eg_server_initialize();

#if 0
    mainloop = g_main_loop_new(NULL, false);
    dbus_connection_setup_with_g_main(conn, NULL);
    g_main_loop_run(mainloop);
#else
    while (1) {
        if (NULL != connection) {
            dbus_connection_read_write_dispatch(connection, 1);
        }
        usleep(1000);
    }
#endif

    dbus_eg_server_release(connection);

    return EXIT_SUCCESS;
}

