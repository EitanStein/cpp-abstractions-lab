#pragma once

#include <future>
#include <chrono>
#include <thread>
#include <print>


namespace AsyncSupport{
    int give_answer_later(){
        std::println("async func: started async func");
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::println("async func: finished sleep on async func");
        return 5;
    }

    std::future<int> get_complicated_answer(bool difficult_calc=true){
        if(difficult_calc)
            return std::async(std::launch::async, AsyncSupport::give_answer_later); // start a bg thread working on it
        else
            return std::async(std::launch::deferred, AsyncSupport::give_answer_later); // start runnning the function when calling get (linear execution on a single thread) 
    }
}

void async_testing(){
    std::future<int> x = std::async(std::launch::async, AsyncSupport::give_answer_later); 
    std::println("main: created future item");
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::println("main: waiting for future to get x");
    std::println("main: x = {}", x.get());


    std::packaged_task<int()> task(AsyncSupport::give_answer_later);
    std::println("main: packed the task");
    std::future<int> task_result = task.get_future();
    std::println("main: set future result of task");
    std::thread worker(std::move(task));
    std::println("main: gave task to worker");
    std::this_thread::sleep_for(std::chrono::milliseconds(100)); // async func will likely start working at this point
    std::println("main: waiting for worker to finish");
    worker.join();
    std::println("main: result = {}", task_result.get());
}