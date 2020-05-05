#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include <thread>
#include <vector>
#include <random>


int randInt() {

    static std::default_random_engine generator;
    static std::uniform_int_distribution<int> distribution(50, 100);
    return distribution(generator);

}

struct BoundedBuffer {
    private:
        int start;
        int end;
        int size;
        std::vector<int> buffer;
        std::mutex m;
        std::condition_variable add_cv;
        std::condition_variable remove_cv;

    public:
        // constructor
        BoundedBuffer(int max_size) {
            start = 0;
            end = max_size - 1;
            size = max_size;
            buffer = std::vector<int>(size);
        }

        void addItem(int item) {
            std::unique_lock<std::mutex> lock(m);
            add_cv.wait(lock, [this] { return start != end; });     // the condition we want is that start != end, i.e. not full

            buffer[start] = item;
            start = (start + 1) % size;
            remove_cv.notify_one();
        }

        int removeItem() {
            std::unique_lock<std::mutex> lock(m);
            remove_cv.wait(lock, [this]{ return ((end + 1) % size) != start; });

            end = (end + 1) % size;
            int item = buffer[end];
            add_cv.notify_one();
            return item;
        }

};

void consumer(BoundedBuffer *bb) {
    for (int i = 0; i < 10; i++) {
        int item = bb->removeItem();
        printf("        consumed item %d\n", item);
        std::this_thread::sleep_for(std::chrono::milliseconds(randInt()));
    }
}

void producer(BoundedBuffer *bb) {
    for (int i = 0; i < 10; i++) {
        int item = randInt();
        printf("produced item %d\n", item);
        bb->addItem(item);
        std::this_thread::sleep_for(std::chrono::milliseconds(randInt()));
    }
}

int main() {

    auto bb = BoundedBuffer(4);

    auto consumer_thread = std::thread([bb_ptr = &bb] { consumer(bb_ptr); });
    auto producer_thread = std::thread([bb_ptr = &bb] { producer(bb_ptr); });

    consumer_thread.join();
    producer_thread.join();

}


