#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/dtypes.h"
#include "../include/misc.h"
#include "../include/sim.h"
#include "../include/benchmark.h"

int debug_flag = 0;
int benchmark_flag = 0;

char settings_file[64] = "settings.json";
char config_file[64] = "config.json";
char benchmark_file[64] = "benchmark.json";

void print_version_and_exit()
{
    printf("algoticks v0.1\n");
    exit(0);
}

void print_help_and_exit()
{

    printf("-V\t\t\tPrint Version and Exit.\n");
    printf("-H\t\t\tPrint this message and Exit.\n\n\n");

    printf("--settings [*.JSON]\t\t\tCustom settings file. Default: settings.json\n");
    printf("--config [*.JSON]\t\t\tCustom config file. Default: config.json\n");
    printf("--benchmark -B [(Optional)[*.JSON]\t\t\tCustom config file. Default: benchmark.json\n");
    exit(0);
}

int main(int argc, char **argv)
{

    if (argc > 1)
    {

        for (int i = 0; i < argc; i++)
        {

            // version
            if (strcmp(argv[i], "-V") == 0)
            {
                print_version_and_exit();
            }

            //help
            else if (strcmp(argv[i], "-H") == 0)
            {
                print_help_and_exit();
            }
            
            //debug
            else if (strcmp(argv[i], "-D") == 0)
            {
                debug_flag = 1;
            }

            // for --settings
            else if (strcmp(argv[i], "--settings") == 0)
            {
                strncpy(settings_file, argv[i + 1], 64);
            }

            // for --config
            else if (strcmp(argv[i], "--config") == 0)
            {
                strncpy(config_file, argv[i + 1], 64);
            }

            // for --benchmark
            else if ((strcmp(argv[i], "--benchmark") == 0) || (strcmp(argv[i], "-B") == 0))
            {
                // if custom .jsom file provided.
                if (i + 1 < argc)
                {
                    strncpy(benchmark_file, argv[i + 1], 64);
                }

                benchmark_flag = 1;
            }

            else
            {
                // unknown arg.
                continue;
            }
        }
    }

    struct Config config;
    struct Settings settings;

    settings = parse_settings_from_json(settings_file);

    //set debug if passed as arg.
    if (debug_flag == 1)
    {
        settings.debug = 1;
    }

    if (benchmark_flag)
    {
        benchmark(benchmark_file, settings);
    }
    else
    {
        config = parse_config_from_json(config_file);
        run_sim(settings, config);
    }

    return 0;
}