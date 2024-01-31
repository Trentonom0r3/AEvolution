# AEvolution: After Effects Scripting Reimagined
-----------------------
`AEvolution` is at the forefront of scripting innovation in Adobe After Effects, offering a revolutionary approach to extend the scripting capabilities of this powerful tool. `AEvolution` is a next-generation plugin that unlocks the potential for users to create custom bindings for scripting in any language.

## Key Features and Benefits:

- Language Agnostic: Prefer Javascript/Typescript? Rust? Write bindings for them!
- Custom Bindings Creation: Empowers users to tailor their scripting experience, creating bindings that suit their workflow and project needs.
- Enhanced Scripting Capabilities: AEvolution brings a new level of control and flexibility to After Effects, enabling advanced custom data processing, effect creation, and more.
- Open-Source Community: As an open-source project, AEvolution thrives on community contributions, ensuring continuous improvement and innovation.
- User-Friendly: Designed with usability in mind, it offers an intuitive interface that simplifies complex scripting tasks.
- Cross-Platform Compatibility: Ensures a consistent experience across different operating systems, enhancing its accessibility to a broader range of users.
- Whether you are a seasoned developer or a creative professional seeking to enhance your After Effects workflow, AEvolution is the perfect tool to elevate your scripting game. Join us in redefining the boundaries of After Effects scripting.

## Contained in this Repo:

- **Dist Folder**: This contains both debug & release builds of the plugin, .dll, and .pyd.

- **AEvolution**: The Core plugin enabling this framework and feature set. This __**should**__ be cross-platform, you may need to compile yourself for other systems outside of `windows[x64]`.
    - No external Dependencies!

- **AEvolutionCore**: The main .dll that is used to create bindings. This includes the headers you'll be using. Python bindings and template link to these specific files.

- **AEvolutionPy**: The .pyd and source code for python bindings. **NOTE** this differs from the final implementation, and not all features from **PyShiftAE** have been refactored and integrated yet.

- **AEvolutionTemplate**: This is a template visual studio project for building your own bindings in any language. Since **AEvolutionCore** already facilitiates communication with the main plugin, your job here is writing bindings using the provided header files, for whatever language you would like. Approaches will differ, but in all cases, link to the **AEvolutionCore.lib** file, and provide the **AEvolutionCore.dll** file upon distribution for your bindings to work. (outside of actually having AEvolution installed). Find more info in this project's `source.cpp` file.

## Requirements (Not provided in this repo):

- **Boost x64 static**
- **Pybind11 static**
