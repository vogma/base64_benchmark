//=============================================================================
// EXTERNAL DEPENDENCIES
//=============================================================================
#include "Base64SurveyRegistry.hpp"
#include "Base64SurveyReport.hpp"
#include "Base64SurveyBenchmark.hpp"

#include <iostream>
#include <filesystem>
#include <vector>

#ifdef _WIN32
#include <Windows.h>
#endif // _WIN32

//=============================================================================
// NAMESPACE IMPORTS
//=============================================================================
using namespace std::chrono;
using namespace std;
using namespace b64_survey;

// static const std::vector<int> test_sizes{32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072, 262144, 524288, 1048576};
static const std::vector<int> test_sizes{1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072, 262144, 524288, 1048576, 2097152, 4194304, 8388608};

int main(int argc, char *argv[])
{
#ifdef _WIN32
    // try to get more consistent results
    SetPriorityClass(GetCurrentProcess(), HIGH_PRIORITY_CLASS);
    SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_HIGHEST);
#endif // _WIN32

    // Run smoke tests on each implementation
    {
        int result = Base64SurveyTests::RunTests(argc + 1, argv);
        // cout << "Press enter to continue." << endl;
        // getchar();
    }

    // Profile the encoders
    {
        cout << endl;
        cout << "*** PROFILING ENCODERS ***" << endl;
        cout << endl;
        MarkdownResultsDelegate liveProgress{test_sizes};
        BenchmarkResults encodeResults = Base64SurveyBenchmark::RunEncodeBenchmark(test_sizes, liveProgress, 1000000, 500ms);

        cout << endl;
        cout << "*** SORTING ENCODER RESULTS ***" << endl;
        cout << endl;
        MarkdownResultsDelegate sortedProgress{test_sizes};
        Base64SurveyReport::PrintSortedResults(encodeResults, sortedProgress);

        // create stat javascript files
        string savedPath = Base64SurveyReport::DumpJsonResult("encode", encodeResults);
        cout << "Saved encoder report to " + savedPath;
    }

    cout << endl;

    // Profile the decoders
    {
        cout << endl;
        cout << "*** PROFILING DECODERS ***" << endl;
        cout << endl;
        MarkdownResultsDelegate liveProgress{test_sizes};
        BenchmarkResults decodeResults = Base64SurveyBenchmark::RunDecodeBenchmark(test_sizes, liveProgress, 1000000, 500ms);

        cout << endl;
        cout << "*** SORTING DECODER RESULTS ***" << endl;
        cout << endl;
        MarkdownResultsDelegate sortedProgress{test_sizes};
        Base64SurveyReport::PrintSortedResults(decodeResults, sortedProgress);

        // create stat javascript files
        std::string savedPath = Base64SurveyReport::DumpJsonResult("decode", decodeResults);
        cout << "Saved decoder report to " + savedPath;
    }

    // cout << "Press enter to continue." << endl;
    // getchar();
    return 0;
}
