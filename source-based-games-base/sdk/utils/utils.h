#pragma once
// #include "../sdk.hpp"

struct key_bind_t
{
	int m_mode_selected = 0;
	int m_key_selected = 0;
};

class c_utils
{
public:
	struct m_key_data_t
	{
		std::array<bool, 256> m_holded_keys{};
		std::array<bool, 256> m_toggled_keys{};
	}m_key_data;

	static uint8_t* find_sig(HMODULE module, const std::string& byte_array);

	__forceinline void** get_vtable(void* instance, size_t offset = 0)
	{
		return *reinterpret_cast<void***>(reinterpret_cast<size_t>(instance) + offset);
	}

	__forceinline const void** get_vtable(const void* instance, size_t offset = 0)
	{
		return *reinterpret_cast<const void***>(reinterpret_cast<size_t>(instance) + offset);
	}

	__forceinline void* get_vfunc(void* instance, size_t index, size_t offset = 0)
	{
		return reinterpret_cast<void*>(get_vtable(instance, offset)[index]);
	}

	template <typename ret_t, typename ... arg_t>
	__forceinline ret_t call_vfunc(void* instance, size_t index, arg_t ... args)
	{
		using _return_t = ret_t(__thiscall*)(void*, decltype(args)...);
		return (*static_cast<_return_t**>(instance))[index](instance, args...);
	}

	template <typename ret_t, typename ... arg_t>
	__forceinline ret_t call_vfunc_offset(void* instance, size_t index, size_t offset = 0, arg_t ... args)
	{
		using _return_t = ret_t(__thiscall*)(void*, decltype(args)...);
		return (*reinterpret_cast<_return_t**>(reinterpret_cast<size_t>(instance) + offset))[index](instance, args...);
	}


	template <typename T>
	static __forceinline T call_vfunc2(void* instance, std::size_t index)
	{
		return (*static_cast<T**>(instance))[index];
	}
	
	bool is_bind_active(key_bind_t key_bind) const;
	void init_key_sys(UINT msg, WPARAM wParam);
	
	static const uint32_t BASE		= 0x811C9DC5;
	static const uint32_t PRIME		= 0x1000193;

	const uint32_t compile_time(const char* data, const uint32_t value = BASE);
	const uint32_t run_time(std::string_view data);

// 	int random_int(int min, int max) const;
// 	float random_float(float min, float max) const;
// 	void random_seed(int seed) const;
};

inline c_utils g_utils = c_utils();