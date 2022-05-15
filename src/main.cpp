#include <boost/system.hpp>
#include <hdr10plus.h>
#include <opencv2/photo.hpp>
#include <opencv2/imgcodecs.hpp>

namespace hdr {
    using namespace cv;

    struct FramesWithMetadata {
        std::vector<Mat> frames;
        std::vector<double> exposure_time;
    };

    Mat hdr_pipeline(Mat& output, const FramesWithMetadata& data) {
        Mat response;
        auto calibrate = createCalibrateDebevec();
        calibrate->process(data.frames, response, data.exposure_time);
        Mat hdr;
        auto merger = createMergeDebevec();
        merger->process(data.frames, hdr, data.exposure_time, response);
        Mat ldr;
        auto tonemap = createTonemapReinhard();
        tonemap->process(hdr, ldr);
        return ldr;
    }


}


