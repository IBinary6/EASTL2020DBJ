
#include "infrastructure/dbj_common.h"

#undef SHORT_SPECIMEN
#define ONE_MILLION 1000000

template < size_t loop_length, unsigned specimen_index_ >
static void performance_test() noexcept
{
	PROLOG;

	static_assert(specimen_index_ < 2);

	constexpr const char* specimen[]{
	"Hello",
	"Hello young fellow from the shallow, why are you so mellow?"
	" Perhaps thy friend is a badfellow?"
	};
	constexpr const char*  str_specimen_ = specimen[specimen_index_];
	constexpr size_t str_specimen_size_  = sizeof(str_specimen_) ;

	printf(VT100_LIGHT_GREEN);
	DBJ_PROMPT("specimen", str_specimen_);
	printf(VT100_RESET);

	DBJ_PROMPT(
		"Test Loop length (millions)", 
		double_to_buff("%03.1f", double(loop_length) / ONE_MILLION).data 
	);

	auto test_loop = [&](auto str_specimen, auto vec_of_strings, auto rezult_prompt) {

		auto seconds_ = [](double E_, double S_) constexpr ->double
		{
			return ((E_)-(S_)) / (CLOCKS_PER_SEC);
		};

		clock_t start{};
		clock_t end{};

		start = clock();
		for (size_t i = 0; i < loop_length; i++)
		{
			vec_of_strings.push_back(str_specimen);
		}
		end = clock();

		DBJ_PROMPT(rezult_prompt, double_to_buff("%f", seconds_(end, start)).data );
	};

	// for fixed eastl versions
	// we can do only small strings
	if constexpr (specimen_index_ == 0 ) {
		// Can hold up to a strlen of str_specimen_size_ + 1.
		// overflow is not taken care of
		// this uses stack and can not be very big 
		using my_fixed_string = eastl::fixed_string<char, str_specimen_size_ + 1, false>;

		// this uses stack and can not be very big 
		using my_fixed_vector = eastl::fixed_vector< my_fixed_string, loop_length + 1, false >;

		test_loop(
			my_fixed_string{ str_specimen_ },
			eastl::vector<my_fixed_string>{},
			"EA STL using fixed string (seconds)"
		);
	}

	test_loop(
		eastl::string{ str_specimen_ },
		eastl::vector<eastl::string>{},
		"EA STL (seconds)"
	);

	// no std lib in kernel mode 
#ifndef _KERNEL_MODE

	test_loop(
		std::string{ str_specimen_ },
		std::vector<std::string>{},
		"STD STL (seconds)"
	);

#else  // ! _KERNEL_MODE
	printf("\n Can not use std lib in kernel mode.");
#endif //!  _KERNEL_MODE
} // performance_test

extern "C"  int testing_sampling(const int argc, char** argv)
{
	constexpr auto dbj_test_loop_size_ = ONE_MILLION / 2 ;

	printf(VT100_LIGHT_BLUE); DBJ_PROMPT( "DBJ EASTL2010" , "" ); printf(VT100_RESET);

#ifdef _KERNEL_MODE
	DBJ_SHOW(_KERNEL_MODE);
#endif // _KERNEL_MODE

#ifdef __clang__
	DBJ_SHOW(__VERSION__);
#else
	DBJ_SHOW(DBJ_STRINGIZE(_MSC_FULL_VER));
#endif

	DBJ_SHOW(DBJ_STRINGIZE(__cplusplus));
	DBJ_SHOW(__TIMESTAMP__);

#ifdef _DEBUG
	DBJ_SHOW(DBJ_STRINGIZE(_DEBUG));
#else
	DBJ_SHOW(DBJ_STRINGIZE(NDEBUG));
#endif
	printf(VT100_RESET);


		performance_test<dbj_test_loop_size_, 0>();
		performance_test<dbj_test_loop_size_, 1>();


	printf(VT100_LIGHT_GREEN "\n\nDone ...\n\n" VT100_RESET);

	return EXIT_SUCCESS;
}