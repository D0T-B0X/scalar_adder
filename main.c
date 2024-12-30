#include <gtk/gtk.h>

typedef struct {
	GtkEntry *val1;
	GtkEntry *val2;
}ValData;

static void free_valdata(GtkWidget *widget, gpointer user_data) {
	ValData *values = (ValData *)user_data;

	g_free(values);
}

int add_values (const char *n1, const char *n2) {
	int num1 = atoi(n1);
	int num2 = atoi(n2);

	return num1 + num2;
}

static void add_entries ( GtkWidget *widget, gpointer user_data) {
	ValData *values = (ValData *)user_data;

	const char *text1 = gtk_editable_get_text(GTK_EDITABLE(values->val1));
	const char *text2 = gtk_editable_get_text(GTK_EDITABLE(values->val2));

	int added_value = add_values(text1, text2);
	g_print("The sum of the values is: %d\n", added_value); 
}

static void activate (GtkApplication *app, gpointer user_data) {
	GtkWidget *window;
	GtkWidget *button;
	GtkWidget *box;

	ValData *values = g_new0(ValData, 1);

	window = gtk_application_window_new(app);
	gtk_window_set_title(GTK_WINDOW(window), "Scalar Addition");
	gtk_window_set_default_size (GTK_WINDOW(window), 400, 400);

	box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
	gtk_window_set_child(GTK_WINDOW(window), box);

	values->val1 = GTK_ENTRY(gtk_entry_new());
	gtk_entry_set_placeholder_text(values->val1, "Type 1st number...");
	gtk_box_append(GTK_BOX(box), GTK_WIDGET(values->val1));

	values->val2 = GTK_ENTRY(gtk_entry_new());
	gtk_entry_set_placeholder_text(values->val2, "Type 2nd number...");
	gtk_box_append(GTK_BOX(box), GTK_WIDGET(values->val2));

	button = gtk_button_new_with_label("Add Values");
	gtk_box_append(GTK_BOX(box), button);

	g_signal_connect(button, "clicked", G_CALLBACK(add_entries), values);
	
	g_signal_connect(window, "destroy", G_CALLBACK(free_valdata), values);

	gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char *argv[]) {

	GtkApplication *app;
	int status;

	app = gtk_application_new("org.scalaraddition.example", G_APPLICATION_DEFAULT_FLAGS);
	g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
	status = g_application_run(G_APPLICATION(app), argc, argv);
	g_object_unref(app);

	return status;
}

