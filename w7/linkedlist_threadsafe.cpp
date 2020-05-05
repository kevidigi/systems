#include <list>
#include <thread>
#include <optional>
#include <mutex>

struct list {
    private:
        std::list<int> list;
        std::mutex mutex;       // this is the mutex we will use to lock critical sections
    public:
        void append_to_list(int value) {
            std::unique_lock<std::mutex> lock(mutex);   // locks the mutex for critical behaviour
            list.push_back(value);
        }                                               // automatically unlocks

        std::optional<int> remove_from_list(int position) {
            std::unique_lock<std::mutex> lock(mutex);   // locks the mutex for critical behaviour
            auto iter = list.begin();
            while (position > 0 && iter != list.end()) {
                iter++;
                position--;
            }
            if (position != 0 || iter == list.end()) {
                return {};                                 // nothing to return (hence optional)
            }
            int value = *iter;
            list.erase(iter);
            return value;
        }                                               // automatically unlocks
};


int main() {
    
    auto l = list{};
    
    l.append_to_list('a');
    l.append_to_list('b');
    l.append_to_list('c');
    
    auto t1 = std::thread([l_ptr = &l] () {l_ptr->remove_from_list(1); });
    auto t2 = std::thread([l_ptr = &l] () {l_ptr->remove_from_list(1); });

    t1.join();
    t2.join();

}
