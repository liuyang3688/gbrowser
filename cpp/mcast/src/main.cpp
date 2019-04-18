#include "../include/mongoose.h" 

#define ADDR_BUF_SIZE 256

static void ev_handler(struct mg_connection *nc, int ev, void *ev_data) {
	switch (ev) {
	case MG_EV_RECV:
		fprintf(stderr, "%.*s", (int)nc->recv_mbuf.len, nc->recv_mbuf.buf);
		nc->recv_mbuf.len = 0;
		break;
	default:
		break;
	}

	(void)ev_data;
}

int main(int argc, char *argv[]) {
	struct mg_mgr mgr;
	char addr[ADDR_BUF_SIZE];

	mg_mgr_init(&mgr, NULL);
	char* strAddr = "239.0.0.100:50000";
	char* strMsg = "AHA";
	snprintf(addr, sizeof(addr), "udp://%s", strAddr);

	fprintf(stderr, "Connecting to '%s'\n", addr);

	struct mg_connect_opts opts;
	opts.flags = MG_F_ENABLE_BROADCAST | IP_ADD_MEMBERSHIP;

	struct mg_connection *nc = mg_connect_opt(&mgr, addr, ev_handler, opts);

	if (nc == NULL) {
		fprintf(stderr, "Failed to connect");
		exit(1);
	}

	fprintf(stderr, "Sending '%s'\n", strMsg);

	mg_send(nc, strMsg, strlen(strMsg));

	fprintf(stderr, "Waiting for data\n");

	for (;;) {
		mg_mgr_poll(&mgr, 10);
	}
	mg_mgr_free(&mgr);

	return 0;
}