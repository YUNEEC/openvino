// Copyright (C) 2018-2021 Intel Corporation
// SPDX-License-Identifier: Apache-2.0
//

///////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "api/primitive.hpp"
#include <vector>

namespace cldnn {
/// @addtogroup cpp_api C++ API
/// @{
/// @addtogroup cpp_topology Network Topology
/// @{
/// @addtogroup cpp_primitives Primitives
/// @{

/// @brief Performs forward calcaulations of input gates for dynamic lstm layer.
/// @details The current implementation of LSTM_DYNAMIC is described the following equations.
///   it = f(Xt*(Wi^T) + Ht-1*Ri + Wbi)
///   ft = f(Xt*(Wf^T) + Ht-1*Rf + Wbf)
///   ct = g(Xt*(Wc^T) + Ht-1*Rc + Wbc)
///   Ct = ft (.) Ct-1 + it (.) ct
///   ot = f(Xt*(Wo^T) + Ht-1*Ro + Wbo)
///   Ht = ot (.) h(Ct)
/// Where f = Sigmoid, g = Tanh, and h = Tanh.
struct lstm_dynamic_timeloop
    : public primitive_base<lstm_dynamic_timeloop> {
    CLDNN_DECLARE_PRIMITIVE(lstm_dynamic_timeloop)

    /// @brief Constructs lstm_dynamic layer.
    /// @param id This primitive id.
    /// @param input Primitive id of input layer.
    /// @param dyn_length Primitive id of ilayer containg dynamic length values (shape: 1D).
    /// @param recurrent Primitive id containing recurrent data.
    /// @param initial_hidden Primitive id containing initial_hidden data. Provide empty string if using lstm_dynamic without initial_hidden values.
    /// @param initial_cell Primitive id containing initial_cell data. Provide empty string if using lstm_dynamic without initial_cell values.
    /// @param clip Clip threshold. Provide 0 if using lstm without activations clip threshold.
    /// @param input_forget Provide 0 if using lstm without coupled input-forget gates.
    lstm_dynamic_timeloop(const primitive_id& id,
                          const primitive_id& input,
                          const primitive_id& dyn_length,
                          const primitive_id& recurrent,
                          const primitive_id& last_hidden_state = "",
                          const primitive_id& last_cell_state = "",
                          const primitive_id& initial_hidden = "",
                          const primitive_id& initial_cell = "",
                          const float clip = 0.0f,
                          const bool input_forget = 0,
                          const primitive_id& ext_prim_id = "",
                          const padding& output_padding = padding())
        : primitive_base(id, {input}, ext_prim_id, output_padding),
          dyn_length(dyn_length),
          recurrent(recurrent),
          last_hidden_state(last_hidden_state),
          last_cell_state(last_cell_state),
          initial_hidden(initial_hidden),
          initial_cell(initial_cell),
          clip(clip),
          input_forget(input_forget) {}

    /// @brief Primitive id containing the dynamic sequence lengths.
    primitive_id dyn_length;
    /// @brief Primitive id containing recurrent data.
    primitive_id recurrent;
    /// @brief Primitive Id of mutable data primitive pointing to buffer, which will be filled with last hidden state.
    primitive_id last_hidden_state;
    /// @brief Primitive Id of mutable data primitive pointing to buffer, which will be filled with last cell state.
    primitive_id last_cell_state;
    /// @brief Primitive id containing the initial value of the hidden data.
    primitive_id initial_hidden;
    /// @brief Array of primitive ids containing the initial value of the hidden state data (Ht-1).
    primitive_id initial_cell;
    /// @brief Cell clip threshold T. It is applied to the input of activations [-T, T]. No clip is applied if it is not specified.
    float clip;
    /// @brief Couple the input and forget gates if input_forget is 1. Default is 0.
    bool input_forget;

protected:
    std::vector<std::reference_wrapper<const primitive_id>> get_dependencies() const override {
        std::vector<std::reference_wrapper<const primitive_id>> ret;
        ret.push_back(dyn_length);
        ret.push_back(recurrent);

        if (!last_hidden_state.empty()) {
            ret.push_back(last_hidden_state);
        }
        if (!last_cell_state.empty()) {
            ret.push_back(last_cell_state);
        }
        if (!initial_hidden.empty()) {
            ret.push_back(initial_hidden);
        }
        if (!initial_cell.empty()) {
            ret.push_back(initial_cell);
        }
        return ret;
    }
};
/// @}
/// @}
/// @}
}  // namespace cldnn
