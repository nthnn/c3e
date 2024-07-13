#include <c3e/tensor.h>
#include <c3e/vector.h>

c3e_tensor* c3e_tensor_init(
    size_t dimension_size,
    uint32_t* dimensions,
    c3e_matrix* layers,
    c3e_vector* data
) {
    assert(dimension_size);
    assert(dimensions != 0);

    assert(layers != NULL);
    assert(data != NULL);

    c3e_tensor* tensor = (c3e_tensor*)
        malloc(sizeof(c3e_tensor));

    tensor->dimensions = dimensions;
    tensor->dimension_size = dimension_size;
    tensor->layers = layers;
    tensor->data = data;

    return tensor;
}

void c3e_tensor_free(c3e_tensor* tensor) {
    assert(tensor != NULL);
    assert(tensor->data != NULL);
    assert(tensor->layers != NULL);

    for(uint32_t i = 0; i < tensor->dimensions; i++)
        c3e_matrix_free(tensor->layers[i]);

    c3e_vector_free(tensor->data);
    free(tensor);
}