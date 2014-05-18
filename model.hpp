#pragma once

#include <string>
#include <vector>

// For distfn_t
#include "dists.hpp"

namespace cv {
    class Mat;
}

struct svm_model;
struct svm_problem;

namespace warco {

    void test_model();

    struct PatchModel {
        PatchModel(std::string distname = "");
        ~PatchModel();

        void add_sample(const cv::Mat& corr, unsigned label);
        double train(const std::vector<double>& C_crossval = {0.1, 1., 10.});
        unsigned predict(const cv::Mat& corr) const;
        std::vector<double> predict_probas(const cv::Mat& corr) const;

        void max_vars(std::vector<float>& vars) const;
        void normalize_covs(const std::vector<float>& max_stddevs);

        void save(std::string name) const;
        void load(std::string name);

        unsigned nlbls() const;

    protected:
        std::vector<cv::Mat> _corrs;
        std::vector<double> _lbls;
        svm_model* _svm;
        svm_problem* _prob;
        double _mean;
        distfn_t _d;

        void free_svm();
    };

} // namespace warco

