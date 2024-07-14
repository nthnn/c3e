<p align="center">
    <img src="assets/c3e-logo.png" alt="C3E Logo" width="128" />
</p>

<h1 align="center">C3E: Complex Compute Core Engine</h1>

The Complex Compute Core Engine (C3E) is a framework library developed in pure C, designed to enhance computational capabilities across various platforms. The library includes four distinct builds, each specifically developed for different use cases, making it a highly adaptable solution for both server computing, desktop and embedded systems. With C3E, developers can build powerful applications that efficiently utilize advanced computational resources, ensuring optimal performance and scalability.

C3E includes an operating system based on Linux for x86 architectures. This build can be deployed as the C3E Processing Unit (C3EPU), a computing accelerator-like that communicates with a host computer via ethernet connection. This setup allows for significant computational offloading, enabling the host system to delegate intensive tasks to the C3EPU. The x86-based C3EPU is ideal for scenarios requiring high-performance computing, such as scientific simulations, large-scale data processing, and complex mathematical computations.

Designed for deployment on embedded systems (such as the Milk-V Duo or Luckfox Pico), C3E also have RISC-V Linux-based program. Despite its smaller size, this version of the C3EPU maintains robust computational capabilities, making it perfect for embedded applications where space and power efficiency are critical. With the use of ethernet for communication, this program ensures smooth integration with other devices within the network, enabling distributed computing across various nodes. This flexibility allows developers to implement sophisticated embedded solutions in fields like IoT, robotics, and edge computing, where efficient and powerful processing is essential.

Additionally, C3E also have a Debian package (*.deb) deployable on Debian-based operating systems. This build functions as a C/C++ library, providing developers with the functionality integrating C3E's capabilities directly into their applications. This library package ensures easy installation and compatibility with a wide range of systems, making it accessible to a broader audience. Developers can harness the power of C3E to enhance their software with advanced computational features, enabling applications to handle more complex tasks and deliver better performance.

Last but not least is the SDK driver, designed for application development, enabling communication with any connected C3EPU. This driver simplifies the process of integrating C3E's advanced computational capabilities into existing applications, providing an interface for developers. The SDK driver ensures that applications can easily leverage the power of C3EPU units, whether deployed on x86 or RISC-V platforms.

## Use Cases

1. **Scientific Research and Simulations**

    The C3E is perfectly suited for scientific research that requires intensive computations, such as simulations in physics, chemistry, and biology. Its ability to handle large matrices and tensors makes it an invaluable tool for modeling complex systems and processes. Researchers can leverage the C3E to perform high-speed calculations, enabling them to explore and analyze phenomena in greater detail and at a faster pace.

2. **Machine Learning and Artificial Intelligence**

    Machine learning algorithms often involve heavy matrix and tensor computations, particularly in areas such as neural network training and inference. The C3E's powerful processing capabilities make it an excellent choice for embedded AI applications, from edge devices to more complex systems. Developers can utilize the C3E to accelerate machine learning tasks, improving the performance and efficiency of AI solutions.

3. **Signal and Image Processing**

    Applications in signal and image processing, such as real-time video analysis, require rapid and accurate mathematical computations. The C3E can efficiently process large volumes of data, making it ideal for tasks like filtering, transformation, and feature extraction. Its high-speed SPI communication ensures minimal latency, crucial for real-time processing applications.

4. **Embedded Systems and IoT**

    The C3E offers a powerful yet compact solution for complex computational tasks. Its efficient processing capabilities make it suitable for a variety of IoT applications, from smart sensors to automated control systems. The C3E can handle data processing locally, reducing the need for constant cloud communication and enhancing the responsiveness and reliability of IoT devices.

## License

The C3E is under two (2) licenses:

1. The source files is under the [BSD 2-Clause License](LICENSE); while,
2. The hardware design, such as schematics and PCB files is under the [CERN Open Hardware License v2 (Strongly Reciprocal)](https://ohwr.org/project/cernohl/-/wikis/uploads/819d71bea3458f71fba6cf4fb0f2de6b/cern_ohl_s_v2.txt).
