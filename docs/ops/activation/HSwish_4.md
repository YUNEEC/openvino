# HSwish {#openvino_docs_ops_activation_HSwish_4}

**Versioned name**: *HSwish-4*

**Category**: *Activation*

**Short description**: HSwish takes one input tensor and produces output tensor where the hard version of swish function is applied to the tensor elementwise.

**Detailed description**: For each element from the input tensor calculates corresponding
element in the output tensor with the following formula: 

\f[
HSwish(x) = x \frac{min(max(x + 3, 0), 6)}{6}
\f]

The HSwish operation is introduced in the following [article](https://arxiv.org/pdf/1905.02244.pdf).

**Attributes**: operation has no attributes.

**Inputs**:

*   **1**: Multidimensional input tensor of type *T*. **Required**.

**Outputs**:

*   **1**: The resulting tensor of the same shape and type as input tensor.

**Types**

* *T*: arbitrary supported floating point type.


**Example**

```xml
<layer ... type="HSwish">
    <input>
        <port id="0">
            <dim>256</dim>
            <dim>56</dim>
        </port>
    </input>
    <output>
        <port id="1">
            <dim>256</dim>
            <dim>56</dim>
        </port>
    </output>
</layer>
```
