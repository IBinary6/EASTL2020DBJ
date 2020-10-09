
#include "infrastructure/dbj_common.h"

//-------------------------------------------------------------------
constexpr size_t ONE_MILLION = 1000000;
constexpr size_t inner_test_loop_size_ = ONE_MILLION * 2 ;
constexpr size_t outer_loop_size{ 10 };

struct test_data {
	constexpr static const char(&small_string)[] {
		"Hello"
	};
	constexpr static const char(&big_string)[] {
		"Hello young fellow from the shallow, why are you so mellow?"
			" Perhaps thy friend is a badfellow?"
	};

	constexpr const char * operator [] (size_t idx_ ) const noexcept 
	{
		if (idx_ > 0 )
			return big_string;
		return small_string;
	}
};
//-------------------------------------------------------------------
template < size_t loop_length, unsigned specimen_index_ >
static auto performance_test() noexcept
{
	constexpr const char* str_specimen_ = test_data{} [specimen_index_] ;
	constexpr size_t str_specimen_size_  = sizeof(str_specimen_) ;

	auto test_loop = [&](auto str_specimen, auto vec_of_strings ) {

		auto seconds_ = [](double E_, double S_) constexpr ->double
		{
			return ((E_)-(S_)) / (CLOCKS_PER_SEC);
		};

		clock_t start = clock();
		for (size_t i = 0; i < loop_length; ++i)
		{
			vec_of_strings.push_back(str_specimen);
		}
		clock_t end = clock();

		return seconds_(end, start) ;
	}; // test_loop

	double eastl_seconds = test_loop(
		eastl::string{ str_specimen_ },
		eastl::vector<eastl::string>{}
	);

	// no std lib in kernel mode 
#ifndef _KERNEL_MODE

	double std_seconds = test_loop(
		std::string{ str_specimen_ },
		std::vector<std::string>{}
	);

#else  // ! _KERNEL_MODE
	double std_seconds = 0;
	printf("\n Can not use std lib in kernel mode.");
#endif //!  _KERNEL_MODE
	struct rezult_struct final
	{ 
      double eastl_rezult{}; 
	  double std_rezult{}; 
	};

return rezult_struct { eastl_seconds , std_seconds } ;

} // performance_test

  //-------------------------------------------------------------------

extern "C"  int testing_sampling(const int argc, char** argv)
{
	printf(VT100_LIGHT_BLUE); DBJ_PROMPT( " " , " " ); 
	printf(VT100_LIGHT_BLUE); DBJ_PROMPT( "DBJ CORE EASTL2020" , "(c) 2020 dbj@dbj.org" );
	printf(VT100_LIGHT_BLUE); DBJ_PROMPT( " " , "dbj.org/license_dbj" );
	printf(VT100_LIGHT_BLUE); DBJ_PROMPT( " " , " " );

#if _HAS_EXCEPTIONS
	DBJ_PROMPT("_HAS_EXCEPTIONS == ", "1");
#else
	DBJ_PROMPT("_HAS_EXCEPTIONS == ", "0");
#endif

#if EASTL_EXCEPTIONS_ENABLED
	DBJ_PROMPT("EASTL_EXCEPTIONS_ENABLED == ", "1");
#else
	DBJ_PROMPT("EASTL_EXCEPTIONS_ENABLED == ", "0");
#endif

#ifdef __clang__
	DBJ_SHOW(__VERSION__);
#else
	DBJ_PROMPT("_MSC_FULL_VER", int_to_buff("%d", _MSC_FULL_VER).data);
#endif

	DBJ_PROMPT("__cplusplus", int_to_buff("%d", __cplusplus).data);
	DBJ_SHOW(__TIMESTAMP__);

#ifdef _DEBUG
	DBJ_PROMPT("_DEBUG", "debug build");
#else
	DBJ_PROMPT("NDEBUG", "release build");
#endif

	DBJ_PROMPT("Testing"," vector of strings");
	DBJ_PROMPT("Outer loop size", int_to_buff("%d", outer_loop_size ).data );
	DBJ_PROMPT(
		"Vector size (millions)",
		double_to_buff("%03.1f", double(inner_test_loop_size_) / ONE_MILLION).data
	);
	DBJ_PROMPT("Test strings", "size");
	DBJ_PROMPT("String 0", int_to_buff("%lu", strlen(test_data{} [0] )).data);
	DBJ_PROMPT("String 1", int_to_buff("%lu", strlen(test_data{} [1] )).data);

	double total_eastl = 0;
	double total_std   = 0;

	for (size_t k = 0 ; k < outer_loop_size; ++k ) {
		auto r_0 = performance_test<inner_test_loop_size_, 0>();

		total_eastl += r_0.eastl_rezult;
		total_std   += r_0.std_rezult;

		auto r_1 = performance_test<inner_test_loop_size_, 1>();

		total_eastl += r_1.eastl_rezult;
		total_std   += r_1.std_rezult;
	}
	DBJ_PROMPT("Accumulated rezults","(seconds on average)");
	printf(VT100_LIGHT_RED );
	DBJ_PROMPT("EASTL        rezult ", double_to_buff("%f", total_eastl / outer_loop_size ).data );
	DBJ_PROMPT("STD STL      rezult ", double_to_buff("%f", total_std / outer_loop_size ).data );
	DBJ_PROMPT("Done ...", "");
	printf("\n");

	return EXIT_SUCCESS;
}