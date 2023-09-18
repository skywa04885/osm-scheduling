#include <iostream>

#include "Config.h"
#include "Scheduler.h"

int main(int argc, char *argv[]) {
    // Makes sure that the config file is given.
    if (argc < 2) {
        std::cerr << "Configuration file has not been specified" << std::endl;
        return -1;
    }

    // Parses the config from the file.
    Config config = Config::ParseFromFile(argv[1]);


    Scheduler scheduler(config.GetJobsAndMove(), config.GetMachinesAndMove());
    scheduler.Schedule();

    return 0;
}
