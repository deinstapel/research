#include <libwebsockets.h>
#include <signal.h>

static int interrupted = 0;

void sigint_handler(int sig) {
  interrupted = 1;
}

int main(int argc, const char* argv) {
  struct lws_context_creation_info info;
  struct lws_context* context;
  int n = 0;

  signal(SIGINT, sigint_handler);
  memset(&info, 0, sizeof info);
  info.port = 7681;
  info.vhost_name = "localhost";
  info.ws_ping_pong_interval = 10;

  context = lws_create_context(&info);
  if (!context) {
    lwsl_err("lws init failed!\n");
    return 1;
  }

  while (n >= 0 && !interrupted) {
    n = lws_service(context, 0);
  }

  lws_context_destroy(context);

  return 0;
}
