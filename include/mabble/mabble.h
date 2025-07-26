#pragma once



#include "../src/core/temp.h"

#include <string>
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

	struct Color
	{
		float r, g, b, a;

		Color() : r(0.0f), g(0.0f), b(0.0f), a(1.0f) {}
		Color(float scalar) : r(scalar), g(scalar), b(scalar), a(1.0f) {}
		Color(float r, float g, float b, float a = 1.0f) : r(r), g(g), b(b), a(a) {}

		bool operator==(const Color& other) const
		{
			return r == other.r && g == other.g && b == other.b && a == other.a;
		}
		bool operator!=(const Color& other) const
		{
			return !(*this == other);
		}
		operator std::string() const
		{
			return ToHexWithAlpha();
		}

		static Color FromRGBA(float r, float g, float b, float a = 1.0f)
		{
			return Color(r / 255.0f, g / 255.0f, b / 255.0f, a);
		}

		static Color FromHex(uint32_t hex)
		{
			float r = ((hex >> 16) & 0xFF) / 255.0f;
			float g = ((hex >> 8) & 0xFF) / 255.0f;
			float b = (hex & 0xFF) / 255.0f;
			return Color(r, g, b);
		}

		static Color FromHex(uint32_t hex, float alpha)
		{
			float r = ((hex >> 16) & 0xFF) / 255.0f;
			float g = ((hex >> 8) & 0xFF) / 255.0f;
			float b = (hex & 0xFF) / 255.0f;
			return Color(r, g, b, alpha);
		}

		static Color FromHex(const std::string& hex)
		{
			if (hex.size() != 7 && hex.size() != 9)
				return Color::White();
			uint32_t color = std::stoul(hex.substr(1), nullptr, 16);
			if (hex.size() == 9) // If alpha is provided
			{
				float alpha = ((color >> 24) & 0xFF) / 255.0f;
				return Color::FromHex(color & 0xFFFFFF, alpha);
			}
			return Color::FromHex(color);
		}

		std::string ToHex() const
		{
			uint32_t rHex = static_cast<uint32_t>(r * 255.0f);
			uint32_t gHex = static_cast<uint32_t>(g * 255.0f);
			uint32_t bHex = static_cast<uint32_t>(b * 255.0f);
			return "#" + std::to_string((rHex << 16) | (gHex << 8) | bHex);
		}
		std::string ToHexWithAlpha() const
		{
			uint32_t rHex = static_cast<uint32_t>(r * 255.0f);
			uint32_t gHex = static_cast<uint32_t>(g * 255.0f);
			uint32_t bHex = static_cast<uint32_t>(b * 255.0f);
			uint32_t aHex = static_cast<uint32_t>(a * 255.0f);
			return "#" + std::to_string((aHex << 24) | (rHex << 16) | (gHex << 8) | bHex);
		}
		
		// Static Colors

		static Color White() { return Color(1.0f, 1.0f, 1.0f); }
		static Color Gray() { return Color(0.5f, 0.5f, 0.5f); }
		static Color Black() { return Color(0.0f, 0.0f, 0.0f); }
		static Color Red() { return Color(1.0f, 0.0f, 0.0f); }
		static Color Green() { return Color(0.0f, 1.0f, 0.0f); }
		static Color Blue() { return Color(0.0f, 0.0f, 1.0f); }
		static Color Yellow() { return Color(1.0f, 1.0f, 0.0f); }
		static Color Cyan() { return Color(0.0f, 1.0f, 1.0f); }
		static Color Magenta() { return Color(1.0f, 0.0f, 1.0f); }
		static Color Transparent() { return Color(0.0f, 0.0f, 0.0f, 0.0f); }
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

	class MABBLE_API VertexBuffer
	{
	public:
		virtual ~VertexBuffer() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetData(const void* data, uint32_t size) = 0;

		virtual const BufferLayout& GetLayout() const = 0;
		virtual void SetLayout(const BufferLayout& layout) = 0;

		static Ref<VertexBuffer> Create(uint32_t size);
		static Ref<VertexBuffer> Create(float* vertices, uint32_t size);
	};

	class MABBLE_API IndexBuffer
	{
	public:
		virtual ~IndexBuffer() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual uint32_t GetCount() const = 0;

		static Ref<IndexBuffer> Create(uint32_t* indices, uint32_t count);

	};

	class MABBLE_API VertexArray
	{
	public:
		virtual ~VertexArray() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) = 0;
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) = 0;

		virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const = 0;
		virtual const Ref<IndexBuffer>& GetIndexBuffer() const = 0;

		static Ref<VertexArray> Create();
	};

	enum class TextureType
	{
		None = 0,
		Texture1D,
		Texture1DArray,
		Texture2D,
		Texture2DArray,
		Texture3D,
		TextureCubeMap,
		TextureCubeMapArray,
		Texture2DMS,
		Texture2DMSArray,
		TextureCube
	};

	enum class ImageFormat
	{
		None = 0,
		RGB,
		RGBA,
		BGR,
		BGRA,
		R8,
		R16F,
		R32F,
		RG8,
		RG16F,
		RG32F,
		RGB8,
		RGB16F,
		RGB32F,
		RGBA8,
		RGBA16F,
		RGBA32F
	};

	struct TextureSpec
	{
		uint32_t Width = 1;
		uint32_t Height = 1;
		ImageFormat Format = ImageFormat::None;
		TextureType Type = TextureType::Texture2D;
		uint32_t Channels = 0;
		bool GenerateMipMaps = true;
	};

	class MABBLE_API Texture
	{
	public:
		virtual ~Texture() = default;

		virtual const TextureSpec& GetSpecification() const = 0;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;
		virtual ImageFormat GetFormat() const = 0;
		virtual uint32_t GetRendererID() const = 0;

		virtual void SetData(const void* data, uint32_t size) = 0;

		virtual void Bind(uint32_t slot = 0) const = 0;

		virtual bool isLoaded() const = 0;

		virtual bool operator==(const Texture& other) const = 0;
	};
}