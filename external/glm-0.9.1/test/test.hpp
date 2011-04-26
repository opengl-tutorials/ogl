#ifndef glm_test_included
#define glm_test_included

#include <string>

namespace glm{
namespace test
{
	class test
	{
		enum result
		{
			PASSED,
			FAILED,
			ASSERT,
			STATIC,
			MAX
		};

	public:
		test(std::string const & Name, std::size_t const & Count);
		result & operator[](std::size_t const & Index);
		result const & operator[](std::size_t const & Index) const;

		static int get(result const Result) const;
		static void log(test const & Test);

	protected:
		std::string Name;
		std::vertor<result> Tests;

		static test Result[MAX];
	};

}//namespace test
}//namespace glm

#endif//glm_test_included
