#include <glib.h>
#include <gio/gio.h>

int main(int argc, char **argv)
{
	g_type_init();

	GError *error = NULL;

	GSocketConnection *connection = NULL;
	GSocketClient *client = g_socket_client_new();

	connection = g_socket_client_connect_to_host(client, (gchar *)"localhost",
			1500, NULL, &error);
	if (NULL != error) {
		g_error(error->message);
	} else {
		g_print("Connection successful!\n");
	}

	GInputStream *istream = g_io_stream_get_input_stream(G_IO_STREAM(connection));
	GOutputStream *ostream = g_io_stream_get_output_stream(G_IO_STREAM(connection));
	g_output_stream_write(ostream, "Hello server!", 13, NULL, &error);
	if (NULL != error) {
		g_error(error->message);
	}

	return 0;
}
