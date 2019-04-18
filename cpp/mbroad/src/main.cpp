#include "../include/mongoose.h" 

static void ev_handler(struct mg_connection *nc, int ev, void *p) {
	struct mbuf *io = &nc->recv_mbuf;
	(void)p;
	switch (ev) {
	case MG_EV_POLL: {
		const char *peer;
		peer = inet_ntoa(nc->sa.sin.sin_addr);
		printf("nc->sa: %s %d\n", peer, ntohs(nc->sa.sin.sin_port));

		break;
	}
	case MG_EV_RECV:
		printf("Received (%zu bytes): '%.*s'\n", io->len, (int)io->len, io->buf);
		mg_send(nc, io->buf, io->len);
		mbuf_remove(io, io->len);
		nc->flags |= MG_F_SEND_AND_CLOSE;
		break;
	default:
		break;
	}
}

int main(int argc, char** argv) {
	struct mg_mgr mgr;
	const char *port1 = "udp://50000";

	mg_mgr_init(&mgr, NULL);
	mg_bind(&mgr, port1, ev_handler);

	printf("Starting echo mgr on ports %s, %s\n", port1);
	for (;;) {
		mg_mgr_poll(&mgr, 1000);
	}
	mg_mgr_free(&mgr);

	return 0;
}