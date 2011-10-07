
__author__ = "eloraiby"
__date__ = "$5-Sep-2010 9:35:29 PM$"

atomic_types = ["unsigned char", "unsigned short", "unsigned int",
		 "signed char", "signed short", "signed int",
		 "float", "double"]


glsl_vector_types = ["tvec2", "tvec3", "tvec4"]
glsl_matrix_types = ["tmat2x2", "tmat2x3", "tmat2x4",
				"tmat3x2", "tmat3x3", "tmat3x4",
				"tmat4x2", "tmat4x3", "tmat4x4"]

glsl_matrix_member_operators = ["+=", "-=", "*=", "/="]
glsl_matrix_out_op_dic = {
						"tmat2x2":"tmat2x2",
						"tmat2x3":"tmat3x3",
						"tmat2x4":"tmat4x4",
						"tmat3x2":"tmat2x2",
						"tmat3x3":"tmat3x3",
						"tmat3x4":"tmat4x4",
						"tmat4x2":"tmat2x2",
						"tmat4x3":"tmat3x3",
						"tmat4x4":"tmat4x4",
						}

glsl_matrix_right_op_dic = {
						"tmat2x2":"tmat2x2",
						"tmat2x3":"tmat3x2",
						"tmat2x4":"tmat4x2",
						"tmat3x2":"tmat2x3",
						"tmat3x3":"tmat3x3",
						"tmat3x4":"tmat4x3",
						"tmat4x2":"tmat2x4",
						"tmat4x3":"tmat3x4",
						"tmat4x4":"tmat4x4",
						}
def gen_vectors():
	for v in glsl_vector_types:
		print
		print "//"
		print "// " + v + " type explicit instantiation"
		print "//"
		for a in atomic_types:
			print "template struct " + v + "<" + a + ">;"
		print

def gen_matrices_member_operators():
	for m in glsl_matrix_types:
		print
		print "//"
		print "// " + m + " type member operator instantiation"
		print "//"
		for a in atomic_types:
			#print "template " + m + "<" + a + ">::col_type;"
			#print "template " + m + "<" + a + ">::row_type;"
			
			for c in atomic_types:
				if a != c:
					print "template " + m + "<" + a + ">::" + m + "(" + m + "<" + c + "> const &m);"  
				
			"""for b in glsl_matrix_member_operators:
				for cm in atomic_types:
					print "template " + m + "<" + a + ">& " + m + "<" + a + ">::operator " + b + "( " + m + "<" + cm + "> const &m);"
					print "template " + m + "<" + a + ">& " + m + "<" + a + ">::operator " + b + "( " + cm + " const &s);"
			
 			"""
 			print
			print "//"
			print "// Binary operators"
			print "//"
			print "template " + m + "<" + a + "> operator + (" + m + "<" + a + "> const &m, " + a + " const &s);"
			if m == "tmat2x2" or m == "tmat3x3" or m == "tmat4x4":
				print "template " + m + "<" + a + "> operator + (" + a + " const &s, " + m + "<" + a + "> const &m);"
			print "template " + m + "<" + a + "> operator + (" + m + "<" + a + "> const &m1, " + m + "<" + a + "> const &m2);"
			
			print "template " + m + "<" + a + "> operator - (" + m + "<" + a + "> const &m, " + a + " const &s);"
			if m == "tmat2x2" or m == "tmat3x3" or m == "tmat4x4":
				print "template " + m + "<" + a + "> operator - (" + a + " const &s, " + m + "<" + a + "> const &m);"
			print "template " + m + "<" + a + "> operator - (" + m + "<" + a + "> const &m1, " + m + "<" + a + "> const &m2);"
			
			out_op = glsl_matrix_out_op_dic[m]
			right_op = glsl_matrix_right_op_dic[m]
			
			print "template " + m + "<" + a + "> operator * (" + m + "<" + a + "> const &m, " + a + " const &s);"
			if m == "tmat2x2" or m == "tmat3x3" or m == "tmat4x4":
				print "template " + m + "<" + a + "> operator * ( " + a + " const &s, " + m + "<" + a + "> const &m);"
			print "template " + out_op + "<" + a + "> operator * (" + m + "<" + a + "> const &m1, " + right_op + "<" + a + "> const &m2);"
			print "template " + m + "<" + a + ">::col_type" + " operator * ( " + m + "<" + a + "> const &m, " + m + "<" + a + ">::row_type" + " const &s);"
			print "template " + m + "<" + a + ">::row_type" + " operator * ( " + m + "<" + a + ">::col_type const &s, " + m + "<" + a + "> const &m);"
			
			print "template " + m + "<" + a + "> operator / (" + m + "<" + a + "> const &m, " + a + " const &s);"
			#print "template " + right_op + "<" + a + "> operator / ( " + a + " const &s, " + m + "<" + a + "> const &m);"
			
			if m == "tmat2x2" or m == "tmat3x3" or m == "tmat4x4":
				print "template " + m + "<" + a + "> operator / ( " + a + " const &s, " + m + "<" + a + "> const &m);"
				#print "template " + m + "<" + a + "> operator / (" + m + "<" + a + "> const &m1, " + m + "<" + a + "> const &m2);"
			else:
				print "template " + m + "<" + a + "> operator / ( " + a + " const &s, " + m + "<" + a + "> const &m);"

			#print "template " + m + "<" + a + ">" + " operator / ( " + m + "<" + a + "> const &m, " + a + " const &s);"
			#print "template " + m + "<" + a + ">" + " operator / ( " + a + " const &s, " + m + "<" + a + "> const &m);"
			
			print
			print "//"
			print "// Unary constant operators"
			print "//"
			print "template " + m + "<" + a + "> const operator -(" + m + "<" + a + "> const &m);"
			print "template " + m + "<" + a + "> const operator --(" + m + "<" + a + "> const &m, int);"
			print "template " + m + "<" + a + "> const operator ++(" + m + "<" + a + "> const &m, int);"
		
		print

def gen_matrices():
	for m in glsl_matrix_types:
		print
		print "//"
		print "// " + m + " type explicit instantiation"
		print "//"
		for a in atomic_types:
			print "template struct " + m + "<" + a + ">;"
		print
		
if __name__ == "__main__":
	print "//"
	print "// GLM External templates generator script version 0.1 for GLM core"
	print "//"
	print "// atomic types:", atomic_types
	print "// GLSL vector types:", glsl_vector_types;
	print "// GLSL matrix types:", glsl_matrix_types;
	print "//"
	print
	print "#include <glm/glm.hpp>"
	print
	print "namespace glm {"
	print "namespace detail {"
	

	gen_vectors()
	gen_matrices()
	gen_matrices_member_operators()

	print "} // namespace detail"
	print "} // namespace glm"
	
	
