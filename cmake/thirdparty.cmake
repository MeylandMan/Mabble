if(NOT DEFINED ENV{VULKAN_SDK})
    message(FATAL_ERROR "Environment variable \"VULKAN_SDK\" not defined.")
endif()

function(register_macro type name path)
    if(type STREQUAL "include")
        set(INCLUDE_DIR_${name} "${path}" PARENT_SCOPE)
    elseif(type STREQUAL "thirdparty")
        set(THIRD_LIBRARY_${name} "${path}" PARENT_SCOPE)
    else()
        message(FATAL_ERROR "Register type incorrect.")
    endif()
endfunction()

register_macro("include" ASSIMP ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/assimp)
register_macro("include" GLAD ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/glad)
register_macro("include" GLM ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/glm)
register_macro("include" GLFW ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/glfw)
register_macro("include" IMGUI ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/imgui)
register_macro("include" MSDF_ATLAS ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/msdf-atlas-gen)
register_macro("include" SPDLOG ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/spdlog)
register_macro("include" STB_IMAGE ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/stb_image)


set(VULKAN_SDK $ENV{VULKAN_SDK})

register_macro("thirdparty" VULKAN "${VULKAN_SDK}/vulkan-1.lib")
register_macro("thirdparty" VULKAN_UTILS "${VULKAN_SDK}/VkLayer_utils.lib")


register_macro("thirdparty" SHADERCD "${VULKAN_SDK}/shaderc_sharedd.lib")
register_macro("thirdparty" SPRIV_CROSSD "${VULKAN_SDK}/spirv-cross-cored.lib")
register_macro("thirdparty" SPRIV_CROSS_GLSLD "${VULKAN_SDK}/spirv-cross-glsld.lib")
register_macro("thirdparty" SPRIV_TOOLSD "${VULKAN_SDK}/SPIRV-Toolsd.lib")

register_macro("thirdparty" SHADERC "${VULKAN_SDK}/shaderc_shared.lib")
register_macro("thirdparty" SPRIV_CROSS "${VULKAN_SDK}/spirv-cross-core.lib")
register_macro("thirdparty" SPRIV_CROSS_GLSL "${VULKAN_SDK}/spirv-cross-glsl.lib")