// compile with: g++ -std=c++14 -I/opt/homebrew/include -DASIO_STANDALONE work_guard_io_context.cpp
// or
// cl /EHsc /std:c++20 /IC:\github\spear\third_party\boost work_guard_io_context.cpp


// some text snippets from io_context source code. This explains why work_guard might be needed in some scenarios.

/// Provides core I/O functionality.
/**
 * @par Stopping the io_context from running out of work
 *
 * Some applications may need to prevent an io_context object's run() call from
 * returning when there is no more work to do. For example, the io_context may
 * be being run in a background thread that is launched prior to the
 * application's asynchronous operations. The run() call may be kept running by
 * using the @ref make_work_guard function to create an object of type
 * boost::asio::executor_work_guard<io_context::executor_type>:
 *
 * @code boost::asio::io_context io_context;
 * boost::asio::executor_work_guard<boost::asio::io_context::executor_type>
 *   = boost::asio::make_work_guard(io_context);
 * ... @endcode
 *
 * To effect a shutdown, the application will then need to call the io_context
 * object's stop() member function. This will cause the io_context run() call
 * to return as soon as possible, abandoning unfinished operations and without
 * permitting ready handlers to be dispatched.
 *
 * Alternatively, if the application requires that all operations and handlers
 * be allowed to finish normally, the work object may be explicitly reset.
 *
 * @code boost::asio::io_context io_context;
 * boost::asio::executor_work_guard<boost::asio::io_context::executor_type>
 *   = boost::asio::make_work_guard(io_context);
 * ...
 * work.reset(); // Allow run() to exit. @endcode
 */

#include <chrono>
#include <iostream>
#include <thread>

#include <boost/asio/executor_work_guard.hpp>
#include <boost/asio/io_context.hpp>

using namespace std::chrono;

typedef boost::asio::executor_work_guard<boost::asio::io_context::executor_type> work_guard_type;

int main()
{
    boost::asio::io_context io_context;
    work_guard_type work_guard(io_context.get_executor());



    // run with work guard enabled
    std::thread my_thread_1([&] {
        std::cout << "    Begin: std::this_thread::sleep_for(5s)\n";
        std::this_thread::sleep_for(5s);
        std::cout << "    End:   std::this_thread::sleep_for(5s)\n";

        std::cout << "    Begin: work_guard.reset()\n";
        work_guard.reset(); // Work guard is destroyed, io_context::run is free to return
        std::cout << "    End:   work_guard.reset()\n";
    });

    std::cout << "Begin: io_context.run()\n";
    io_context.run();
    std::cout << "End:   io_context.run()\n";

    std::cout << "Begin: my_thread_1.join()\n";
    my_thread_1.join();
    std::cout << "End:   my_thread_1.join()\n\n\n";



    // run without resetting the state of the work guard
    std::cout << "Begin: io_context.restart()\n";
    io_context.restart();
    std::cout << "End:   io_context.restart()\n";

    std::cout << "Begin: io_context.run()\n";
    io_context.run();
    std::cout << "End:   io_context.run()\n\n\n";



    // run with resetting the state of the work guard
    std::cout << "Begin: io_context.restart()\n";
    io_context.restart();
    std::cout << "End:   io_context.restart()\n";

    // force a full reset of the work guard state without allocating any memory using the placement-new operator
    std::cout << "Begin: new(&work_guard) work_guard_type(io_context.get_executor())\n";
    new(&work_guard) work_guard_type(io_context.get_executor());
    std::cout << "End:   new(&work_guard) work_guard_type(io_context.get_executor())\n";

    // run with work_guard enabled
    std::thread my_thread_2([&] {
        std::cout << "    Begin: std::this_thread::sleep_for(5s)\n";
        std::this_thread::sleep_for(5s);
        std::cout << "    End:   std::this_thread::sleep_for(5s)\n";

        std::cout << "    Begin: work_guard.reset()\n";
        work_guard.reset(); // Work guard is destroyed, io_context::run is free to return
        std::cout << "    End:   work_guard.reset()\n";
    });

    std::cout << "Begin: io_context.run()\n";
    io_context.run();
    std::cout << "End:   io_context.run()\n";

    std::cout << "Begin: my_thread_2.join()\n";
    my_thread_2.join();
    std::cout << "End:   my_thread_2.join()\n\n\n";
}
