#pragma once



#include "../src/core/temp.h"

#include <vector>
#include <cstdint>
#include <cstring>

#if defined(MABBLE_SHARED_BUILD)
#   if defined(_MSC_VER)
#       if defined(MABBLE_BUILD)
#			define MABBLE_API __declspec(dllexport)
#       else
#           define MABBLE_API __declspec(dllimport)
#       endif
#   elif defined(__GNUC__)
#       define MABBLE_API __attribute__((visibility("default")))
#   else
#       define MABBLE_API
#	    pragma warning "Mabble Dynamic link is not supported in this compiler yet"
#   endif
#else
#   define MABBLE_API
#endif

#if defined(MABBLE_DEBUG)
	#define MABBLE_ENABLE_ASSERTS 1
	#if MABBLE_ENABLE_ASSERTS
		#include <assert.h>
		#define MABBLE_ASSERT(x) assert(x)
	#endif
#endif

namespace Mabble
{
	// ---------------------------------------------------------
	// TODO: Create a proper Memory Management System
	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
	// ---------------------------------------------------------


	enum class GAPI : uint8_t
	{
		None,
		OpenGL
	};



	// ---------------------------------------------------------
	struct Buffer
	{
		uint8_t* Data = nullptr;
		uint64_t Size = 0;

		Buffer() = default;

		Buffer(uint64_t size)
		{
			Allocate(size);
		}

		Buffer(const Buffer&) = default;

		static Buffer Copy(Buffer other)
		{
			Buffer result(other.Size);
			memcpy(result.Data, other.Data, other.Size);
			return result;
		}

		void Allocate(uint64_t size)
		{
			Release();

			Data = new uint8_t[size];
			Size = size;
		}

		void Release()
		{
			if (Data)
			{
				delete[] Data;
				Data = nullptr;
				Size = 0;
			}
		}

		template<typename T>
		T* As()
		{
			return (T*)Data;
		}

		operator bool() const
		{
			return (bool)Data;
		}
	};

	struct ScopedBuffer 
	{
		ScopedBuffer(Buffer buffer)
			: m_Buffer(buffer)
		{
		}

		ScopedBuffer(uint64_t size)
			: m_Buffer(size)
		{
		}

		~ScopedBuffer()
		{
			m_Buffer.Release();
		}

		uint8_t* Data() { return m_Buffer.Data; }
		uint64_t Size() { return m_Buffer.Size; }

		template<typename T>
		T* As()
		{
			return m_Buffer.As<T>();
		}

		operator bool() const { return m_Buffer; }
	private:
		Buffer m_Buffer;
	};



	enum class ShaderDataType
	{
		None = 0,
		Float,
		Float2,
		FLoat3,
		Float4,
		Mat3,
		Mat4,
		Int,
		Int2,
		Int3,
		Int4,
		Bool
	};

	static uint32_t ShaderDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::None:   return 0;
		case ShaderDataType::Float:  return sizeof(float);
		case ShaderDataType::Float2: return sizeof(float) * 2;
		case ShaderDataType::FLoat3: return sizeof(float) * 3;
		case ShaderDataType::Float4: return sizeof(float) * 4;
		case ShaderDataType::Mat3:   return sizeof(float) * 3 * 3;
		case ShaderDataType::Mat4:   return sizeof(float) * 4 * 4;
		case ShaderDataType::Int:    return sizeof(int32_t);
		case ShaderDataType::Int2:   return sizeof(int32_t) * 2;
		case ShaderDataType::Int3:   return sizeof(int32_t) * 3;
		case ShaderDataType::Int4:   return sizeof(int32_t) * 4;
		case ShaderDataType::Bool:   return sizeof(bool);
		default:
			MABBLE_ASSERT(false && "Unknown ShaderDataType !");
			return 0;
		}
	}

	struct BufferElement
	{
		std::string Name;
		ShaderDataType Type;
		uint32_t Size;
		uint32_t Offset;
		bool Normalized;
		BufferElement() = default;
		BufferElement(ShaderDataType type, const std::string& name, bool normalized = false)
			: Name(name), Type(type), Size(ShaderDataTypeSize(type)), Offset(0), Normalized(normalized)
		{
		}
		uint32_t GetComponentCount() const
		{
			switch (Type)
			{
			case ShaderDataType::Float:  return 1;
			case ShaderDataType::Float2: return 2;
			case ShaderDataType::FLoat3: return 3;
			case ShaderDataType::Float4: return 4;
			case ShaderDataType::Mat3:   return 3 * 3;
			case ShaderDataType::Mat4:   return 4 * 4;
			case ShaderDataType::Int:    return 1;
			case ShaderDataType::Int2:   return 2;
			case ShaderDataType::Int3:   return 3;
			case ShaderDataType::Int4:   return 4;
			case ShaderDataType::Bool:   return 1;
			default:
				MABBLE_ASSERT(false && "Unknown ShaderDataType !");
				return 0;
			}
		}
	};

	class MABBLE_API BufferLayout
	{
	public:
		BufferLayout() {}

		BufferLayout(std::initializer_list<BufferElement> elements)
			: m_Elements(elements)
		{
			CalculateOffsetsAndStride();
		}

		uint32_t GetStride() const { return m_Stride; }
		const std::vector<BufferElement>& GetElements() const { return m_Elements; }

		std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
		std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }
		std::vector<BufferElement>::const_iterator cbegin() const { return m_Elements.cbegin(); }
		std::vector<BufferElement>::const_iterator cend() const { return m_Elements.cend(); }
	private:
		void CalculateOffsetsAndStride()
		{
			uint32_t offset = 0;
			m_Stride = 0;
			for (auto& element : m_Elements)
			{
				element.Offset = offset;
				offset += element.Size;
				m_Stride += element.Size;
			}
		}
	private:
		std::vector<BufferElement> m_Elements;
		uint32_t m_Stride = 0;
	};


}