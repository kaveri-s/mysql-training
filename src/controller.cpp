// #include "parser.tab.hh"
#include "controller.hpp"

using namespace std;


// int main()
// {
//     cout << "Hi\n";
//     yyin = fopen("../test/lex", "r");
//     yyparse();
//     cout << "Bye\n";
// }

int main(int argc, char **argv)
  {
    _cust_check_startup();
    (void) thr_setconcurrency(concurrency);
    init_ssl();
    server_init();                             // 'bind' + 'listen'
    init_server_components();
    start_signal_handler();
    acl_init((THD *)0, opt_noacl);
    init_slave();
    create_shutdown_thread();
    create_maintenance_thread();
    handle_connections_sockets(0);             // !
    DBUG_PRINT("quit",("Exiting main thread"));
    exit(0);
  }