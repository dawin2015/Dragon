// --------------------------------------------------------
// Dragon
// Copyright(c) 2017 SeetaTech
// Written by Ting Pan
// --------------------------------------------------------

#ifndef DRAGON_OPERATORS_VISION_BILINEAR_RESIZE_OP_H_
#define DRAGON_OPERATORS_VISION_BILINEAR_RESIZE_OP_H_

#include "core/operator.h"

namespace dragon {

template <class Context>
class BilinearResizeOp : public Operator<Context> {
 public:
    BilinearResizeOp(const OperatorDef& op_def, Workspace* ws)
        : Operator<Context>(op_def, ws),
          dsize_desc(OperatorBase::GetRepeatedArg<string>("dsize")),
          fy(OperatorBase::GetSingleArg<float>("fy", -1.0)),
          fx(OperatorBase::GetSingleArg<float>("fx", -1.0)),
          data_format(OperatorBase::GetSingleArg<string>("data_format", "NCHW")) {
        if (data_format == "NCHW") spatial_axis = 2;
        else if (data_format == "NHWC") spatial_axis = 1;
        else LOG(FATAL) << "Unknown data format: " << data_format;
    }
    void RunOnDevice() override;
    template <typename T> void RunWithType();

 protected:
    vector<string> dsize_desc;
    float fy, fx;
    string data_format;
    TIndex n, c, h, w, out_h, out_w, spatial_axis;
    vector<TIndex> dims;
};

template <class Context>
class BilinearResizeGradientOp : public Operator<Context> {
 public:
    BilinearResizeGradientOp(const OperatorDef& op_def, Workspace* ws)
        : Operator<Context>(op_def, ws),
          data_format(OperatorBase::GetSingleArg<string>("data_format", "NCHW")) {}

    void RunOnDevice() override;
    template <typename T> void RunWithType();

 protected:
    string data_format;
    TIndex n, c, h, w, out_h, out_w;
};

}    // namespace dragon

#endif    // DRAGON_OPERATORS_VISION_BILINEAR_RESIZE_OP_H_