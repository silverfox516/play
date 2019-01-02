#include <glib.h>
#include <gio/gio.h>

static GInetAddress *get_localhost()
{
	GInetAddress *addr = g_inet_address_new_any(G_SOCKET_FAMILY_IPV4);
	if (!addr) {
		addr = g_inet_address_new_any(G_SOCKET_FAMILY_IPV6);
	}

	return addr;
}

gboolean incoming_callback(GSocketService *service, GSocketConnection *connection,
		GObject *source_object, gpointer user_data)
{
	g_print("Received connection from client!\n");
	GInputStream *istream = g_io_stream_get_input_stream(G_IO_STREAM(connection));
	gchar message[1024];
	g_input_stream_read(istream, message, 1024, NULL, NULL);
	g_print("Message was: \"%s\n", message);
	return FALSE;
}

int main(int argc, char **argv)
{
	g_type_init();

	if (!g_thread_supported())
		g_thread_init(NULL);

	GError *error = NULL;

	GSocketService *service = g_threaded_socket_service_new(10);

	GInetAddress *inet_addr = get_localhost();
	GSocketAddress *sock_addr = g_inet_socket_address_new(inet_addr, 1500);

	GSocketAddress *effective_addr;
	g_socket_listener_add_address(G_SOCKET_LISTENER(service), sock_addr,
			G_SOCKET_TYPE_STREAM, G_SOCKET_PROTOCOL_TCP, NULL,
			&effective_addr, &error);

	if (NULL != error) {
		g_error(error->message);
	}

	g_signal_connect(service, "incoming", G_CALLBACK(incoming_callback), NULL);

	g_socket_service_start(service);

	g_print("Waiting for client!\n");
	GMainLoop *loop = g_main_loop_new(NULL, FALSE);
	g_main_loop_run(loop);
	g_main_loop_unref(loop);

	return 0;
}
