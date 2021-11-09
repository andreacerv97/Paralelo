#include <iostream>
#include<random>
#include<cmath>
#include<iomanip>
#include<future>
#include<thread>


struct vect{
    double x = 0.000;
    double y = 0.000;
    double z = 0.000;
};

struct Objects{
    vect pos;
    vect vel;
    vect ac;
    double  m;
    int flag = 1;
};


void assign_x(Objects *objs, int seed, long int num_objects, double size_enclosure){
    std::mt19937_64 generator(seed);
    std::uniform_real_distribution<> dis(0, size_enclosure);
    std::normal_distribution<> d{1e21, 1e15};
    for(int i = 0;i < num_objects;++i){
        objs[i].pos.x = dis(generator);
        objs[i].m = d(generator);
        objs[i].flag = 1;
    }
}



void assign_y(Objects *objs, int seed, long int num_objects, double size_enclosure){
    std::mt19937_64 generator(seed);
    std::uniform_real_distribution<> dis(0, size_enclosure);
    for(int i = 0; i < num_objects;++i){
        objs[i].pos.y = dis(generator);
    }
}

void assign_z(Objects *objs, int seed, long int num_objects, double size_enclosure){
    std::mt19937_64 generator(seed);
    std::uniform_real_distribution<> dis(0, size_enclosure);
    for(int i = 0; i < num_objects; ++i){
        objs[i].pos.z = dis(generator);
    }
}



int main(int argc, char *argv[]) {
    // first argument checking
    if(argc != 6){
        //incorrect number of arguments
        // if the number of parameters is incorrect we return -1
        if(argc == 1){
            std::cout<<"\tnum_objects: ?\n";
            std::cout<<"\tnum_iterations: ?\n";
            std::cout<<"\tseed: ?\n";
            std::cout<<"\tsize_enclosure: ?\n";
            std::cout<<"\ttime_step: ?\n";
        }
        else if(argc == 2)
        {
            std::cout<<"\tnum_objects: "<<argv[1]<<"\n";
            std::cout<<"\tnum_iterations: ?\n";
            std::cout<<"\tseed: ?\n";
            std::cout<<"\tsize_enclosure: ?\n";
            std::cout<<"\ttime_step: ?\n";
        }
        else if(argc == 3)
        {
            std::cout<<"\tnum_objects: "<<argv[1]<<"\n";
            std::cout<<"\tnum_iterations: "<<argv[2]<<"\n";
            std::cout<<"\tseed: ?\n";
            std::cout<<"\tsize_enclosure: ?\n";
            std::cout<<"\ttime_step: ?\n";
        }
        else if(argc == 4)
        {
            std::cout<<"\tnum_objects: "<<argv[1]<<"\n";
            std::cout<<"\tnum_iterations: "<<argv[2]<<"\n";
            std::cout<<"\tseed: "<<argv[3]<<"\n";
            std::cout<<"\tsize_enclosure: ?\n";
            std::cout<<"\ttime_step: ?\n";
        }
        else if(argc == 5)
        {
            std::cout<<"\tnum_objects: "<<argv[1]<<"\n";
            std::cout<<"\tnum_iterations: "<<argv[2]<<"\n";
            std::cout<<"\tseed: "<<argv[3]<<"\n";
            std::cout<<"\tsize_enclosure: "<<argv[4]<<"\n";
            std::cout<<"\ttime_step: ?\n";
        }
        else
        {
            std::cout<<"\tnum_objects: "<<argv[1]<<"\n";
            std::cout<<"\tnum_iterations: "<<argv[2]<<"\n";
            std::cout<<"\tseed: "<<argv[3]<<"\n";
            std::cout<<"\tsize_enclosure: "<<argv[4]<<"\n";
            std::cout<<"\ttime_step: "<<argv[5]<<"\n";
        }
        return -1;
    }
    // when the number of parameters is correct we must check whether they have legal values or not
    // first we must check that num_objects and num_iterations are non-negative integers
    char *end1, *end2, *end3, *end4, *end5;
    double size_enclosure, time_step;
    //int num_objects;
    long int num_objects, num_iterations, seed; //quitado num_objects
    num_objects= strtol(argv[1], &end1, 10);
    num_iterations = strtol(argv[2], &end2, 10);
    seed = strtol(argv[3], &end3, 10);
    size_enclosure = strtof(argv[4], &end4);
    time_step = strtof(argv[5], &end5);

    if ((*end1 != '\0')||(*end2 != '\0')||(*end3 != '\0')||(*end4 != 0) ||(*end5 != 0 )) {
        // then num_objects or num_iterations or the seed or all of them are not an integer, thus we must return -2
        //print_parameters(reinterpret_cast<char *>(*argv));
        std::cout<<"\tnum_objects: "<<argv[1]<<"\n";
        std::cout<<"\tnum_iterations: "<<argv[2]<<"\n";
        std::cout<<"\tseed: "<<argv[3]<<"\n";
        std::cout<<"\tsize_enclosure: "<<argv[4]<<"\n";
        std::cout<<"\ttime_step: "<<argv[5]<<"\n";

        return -2;
    }
    // now we must check if they are non-negative
    if((num_objects < 0)||(num_iterations<0)||(seed <= 0)||(size_enclosure < 0)||(time_step < 0)) {
        // if one of them has an illegal value, we return -2
        //print_parameters(reinterpret_cast<char *>(*argv));
        std::cout<<"\tnum_objects: "<<argv[1]<<"\n";
        std::cout<<"\tnum_iterations: "<<argv[2]<<"\n";
        std::cout<<"\tseed: "<<argv[3]<<"\n";
        std::cout<<"\tsize_enclosure: "<<argv[4]<<"\n";
        std::cout<<"\ttime_step: "<<argv[5]<<"\n";

        return -2;
    }

    // we need to initialize the random position for each of the objects and write it into a file
    // the content of the file must have the following format

    //print_parameters(reinterpret_cast<char **>(argv));
    std::cout<<"\tnum_objects: "<<argv[1]<<"\n";
    std::cout<<"\tnum_iterations: "<<argv[2]<<"\n";
    std::cout<<"\tseed: "<<argv[3]<<"\n";
    std::cout<<"\tsize_enclosure: "<<argv[4]<<"\n";
    std::cout<<"\ttime_step: "<<argv[5]<<"\n";

    auto *objs = new Objects[num_objects];



    std::thread t1 {assign_x, std::ref(*objs), (seed), (num_objects), (size_enclosure)};
    std::thread t2 {assign_y, std::ref(*objs), std::ref(seed), std::ref(num_objects), std::ref(size_enclosure)};
    std::thread t3 {assign_z, std::ref(*objs), std::ref(seed), std::ref(num_objects), std::ref(size_enclosure)};
    // we wait for the termination of the assignment threads
    t1.join();
    t2.join();
    t3.join();





    return 0;
}
