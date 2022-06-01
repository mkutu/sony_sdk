#include <cstdlib>
#if defined(USE_EXPERIMENTAL_FS)
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;
#else
#include <filesystem>
namespace fs = std::filesystem;
#if defined(__APPLE__)
#include <unistd.h>
#endif
#endif
#include <cstdint>
#include <iomanip>
#include "CRSDK/CameraRemote_SDK.h"
#include "CameraDevice.h"
#include "Text.h"
#include <chrono>
#include <thread>

namespace SDK = SCRSDK;

int main()
{
    // Change global locale to native locale
    std::locale::global(std::locale(""));
    using namespace std::this_thread;     // sleep_for, sleep_until
    using namespace std::chrono_literals; // ns, us, ms, s, h, etc.
    using std::chrono::system_clock;

    auto init_success = SDK::Init();
    // Enumerte connected cameras
    SDK::ICrEnumCameraObjectInfo *camera_list = nullptr;
    auto enum_status = SDK::EnumCameraObjects(&camera_list);
    auto camera_info = camera_list->GetCameraObjectInfo(0);
    //IDeviceCallback function below this line
    typedef std::shared_ptr<cli::CameraDevice> CameraDevicePtr;
    typedef std::vector<CameraDevicePtr> CameraDeviceList;
    CameraDeviceList cameraList; // all
    std::int32_t cameraNumUniq = 1;
    std::int32_t selectCamera = 1;
    // this is IDeviceCallback function
    CameraDevicePtr camera = CameraDevicePtr(new cli::CameraDevice(cameraNumUniq, nullptr, camera_info));
    cameraList.push_back(camera); // add 1st
    cli::tout << camera << " Camera.\n";
    // IDK why we release the camera list here
    camera_list->Release();
    
    //connect
    camera->connect(SDK::CrSdkControlMode_Remote);
    sleep_for(3s);
    camera->af_shutter();
    sleep_for(2s);
    // cli::tout << "Something.\n";


    cli::tout << "Release SDK resources.\n";
    SDK::Release();
    cli::tout << "Exiting application.\n";
    std::exit(EXIT_SUCCESS);

}
//     cli::tsmatch smatch;
//     CrInt32u no = 0;




//     cli::tsmatch smatch;
//     CrInt32u no = 1;



//     typedef std::shared_ptr<cli::CameraDevice> CameraDevicePtr;
//     typedef std::vector<CameraDevicePtr> CameraDeviceList;
//     CameraDeviceList cameraList; // all
//     std::int32_t cameraNumUniq = 1;
//     std::int32_t selectCamera = 1;

//     cli::tout << "Connect to selected camera...\n";
//     auto *camera_info = camera_list->GetCameraObjectInfo(no - 1);

//     cli::tout << "Create camera SDK camera callback object.\n";
//     CameraDevicePtr camera = CameraDevicePtr(new cli::CameraDevice(cameraNumUniq, nullptr, camera_info));
//     cameraList.push_back(camera); // add 1st
    
//     sleep_for(2s);
//     camera->connect(SDK::CrSdkControlMode_Remote);
//     sleep_for(3s);
//     camera->af_shutter();
//     cli::tout << std::endl;
//     cli::tout << "Release SDK resources.\n";
//     SDK::Release();
//     cli::tout << "Exiting application.\n";
//     std::exit(EXIT_SUCCESS);
// }
