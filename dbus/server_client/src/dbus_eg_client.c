#include <stdio.h>
#include <stdlib.h>
#include <dbus/dbus.h>

#define LOG_TAG		"client : "

#define NAME_BUS        "com.igsong.dbus"
#define NAME_OBJECT     "/com/igsong/dbus"

DBusMessage *client_send_message(DBusConnection *connection,
        DBusMessage *message)
{
    DBusMessage *reply = NULL;
    DBusPendingCall *pending = NULL;

    if (!dbus_connection_send_with_reply(connection, message, &pending, -1)) {
        fprintf(stderr, LOG_TAG "dbus_connection_send_with_reply() failed\n");
        goto out;
    }

    if (NULL == pending) {
        fprintf(stderr, LOG_TAG "pending call is null\n");
        goto out;
    }

    dbus_connection_flush(connection);
    dbus_pending_call_block(pending);
    reply = dbus_pending_call_steal_reply(pending);
    if (NULL == reply) {
        fprintf(stderr, LOG_TAG "dbus_pending_call_steal_reply() returns NULL\n");
        goto out;
    }

out:
    if (pending)
	    dbus_pending_call_unref(pending);

    return reply;
}

DBusMessage *get_message_hello()
{
    DBusMessage *message = NULL;
    DBusMessageIter args;
    const char *iam = "igsong";

    message = dbus_message_new_method_call(NAME_BUS, NAME_OBJECT, NAME_BUS".Conversation", "Hello");
    if (NULL == message) {
        fprintf(stderr, LOG_TAG "dbus_message_new_method_call() failed\n");
        goto fail;
    }

    dbus_message_iter_init_append(message, &args);
    if (!dbus_message_iter_append_basic(&args, DBUS_TYPE_STRING, &iam)) {
        fprintf(stderr, LOG_TAG "dbus_message_iter_append_basic() failed\n");
        goto fail;
    }

    return message;
fail:
    if (!message)
        dbus_message_unref(message);
    return NULL;
}

DBusMessage *get_message_introspect()
{
    DBusMessage *message = NULL;
    DBusMessageIter args;
    const char *method = "GetAll";

    message = dbus_message_new_method_call(NAME_BUS, NAME_OBJECT, NAME_BUS".Introspectable", "Introspect");
    if (NULL == message) {
        fprintf(stderr, LOG_TAG "dbus_message_new_method_call() failed\n");
        goto fail;
    }

    return message;
fail:
    if (!message)
        dbus_message_unref(message);
    return NULL;
}

int main(int argc, char argv[])
{
    printf(LOG_TAG "hello, this is a client.\n");
    
    DBusConnection *connection = NULL;
    DBusMessage *message, *reply = NULL;
    DBusMessageIter args;
    DBusHandlerResult result = DBUS_HANDLER_RESULT_HANDLED;
    DBusError error;
    char *answer;

    const char *dbus_session_bus_address = getenv("DBUS_SESSION_BUS_ADDRESS");
    printf(LOG_TAG "DBUS_SESSION_BUS_ADDRESS : %s\n", dbus_session_bus_address);

    dbus_error_init(&error);

    if (NULL != dbus_session_bus_address) {
	    if ((connection = dbus_connection_open(dbus_session_bus_address, &error)) == NULL ||
			    !dbus_bus_register(connection, &error))
	    if (dbus_error_is_set(&error)) {
		    fprintf(stderr, LOG_TAG "dbus_connection_open() failed, %s\n", error.message);
		    dbus_error_free(&error);
		    dbus_connection_unref(connection);
	    }
    }
    if (!connection) {
	    printf(LOG_TAG "trying to get bus BUS_BUS_SESSION");
	    connection = dbus_bus_get(DBUS_BUS_SESSION, &error);
	    if (dbus_error_is_set(&error)) {
		    fprintf(stderr, LOG_TAG "dbus_error_init() failed, %s\n", error.message);
		    goto fail;
	    }
    }
    printf(LOG_TAG "connected to %s\n", dbus_connection_get_server_id(connection));

    result = dbus_bus_request_name(connection, NAME_BUS".client",
            DBUS_NAME_FLAG_REPLACE_EXISTING, &error);
    if (DBUS_REQUEST_NAME_REPLY_PRIMARY_OWNER != result) {
        fprintf(stderr, LOG_TAG "dbus_bus_request_name() failed, %s\n", error.message);
        goto fail;
    }

#if 1
    message = get_message_hello();
    if (NULL == message) {
        fprintf(stderr, LOG_TAG "get_message_hello() failed\n");
        goto fail;
    }

    reply = client_send_message(connection, message);
    if (NULL == reply) {
        fprintf(stderr, LOG_TAG "client_send_message() failed, %d\n", result);
        goto fail;
    }

    if (!dbus_message_iter_init(reply, &args)) {
        fprintf(stderr, LOG_TAG "dbus_message_iter_init() failed\n");
        goto fail;
    }

    while (dbus_message_iter_get_arg_type(&args) != DBUS_TYPE_INVALID) {
	    dbus_message_iter_get_basic(&args, &answer);
	    dbus_message_iter_next(&args);
	    printf(LOG_TAG "got %s\n", answer);
    }
#endif

#if 2
    message = get_message_introspect();
    if (NULL == message) {
        fprintf(stderr, LOG_TAG "get_message_hello() failed\n");
        goto fail;
    }

    reply = client_send_message(connection, message);
    if (NULL == reply) {
        fprintf(stderr, LOG_TAG "client_send_message() failed, %d\n", result);
        goto fail;
    }

    if (!dbus_message_iter_init(reply, &args)) {
        fprintf(stderr, LOG_TAG "dbus_message_iter_init() failed\n");
        goto fail;
    }

    while (dbus_message_iter_get_arg_type(&args) != DBUS_TYPE_INVALID) {
	    dbus_message_iter_get_basic(&args, &answer);
	    dbus_message_iter_next(&args);
	    printf(LOG_TAG "got %s\n", answer);
    }
#endif

fail:
    dbus_error_free(&error);
    if (message)
        dbus_message_unref(message);
    if (reply)
        dbus_message_unref(reply);
    if (connection) {
        dbus_connection_unref(connection);
    }
    return 0;
}


