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
		mbuf_remove(io, io->len);
		nc->flags |= MG_F_SEND_AND_CLOSE;
		break;
	default:
		break;
	}
}
#define MCAST_GROUP "239.0.0.100"
#define INTERFACE "0.0.0.0"
//#define INTERFACE "169.254.219.236"
int main(int argc, char** argv) {
	struct mg_mgr mgr;
	struct mg_connection *nc;
	const char *mcast_group = MCAST_GROUP;
	const char *eth = INTERFACE;
	mg_mgr_init(&mgr, NULL);
	nc = mg_bind(&mgr, "udp://50000", ev_handler);
	if (nc == NULL) {
		perror("cannot bind\n");
		exit(1);
	}
	ip_mreq multiCast;
	multiCast.imr_multiaddr.S_un.S_addr = inet_addr(mcast_group);
	multiCast.imr_interface.S_un.S_addr = inet_addr(eth);
	if (setsockopt(nc->sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char*)&multiCast, sizeof(multiCast)) != 0) {
		perror("Adding multicast group error");
		exit(1);
	}
	printf("Starting mcast server on port 1234 listening to group %s\n", mcast_group);
	for (;;) {
		mg_mgr_poll(&mgr, 1000);
	}
	mg_mgr_free(&mgr);
	return 0;
}