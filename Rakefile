require 'rubygems' if RUBY_VERSION < '1.9'
require 'rake/builder'

Rake::Builder.new do |builder|
	builder.target = 'library/libnanovg.a'
	builder.programming_language = 'c'
	builder.source_search_paths = ['nanovg/src']
	builder.compiler = 'clang'
	builder.linker = 'clang'
	builder.objects_path = 'nanovg'
	builder.include_paths = ['nanovg/src']
	builder.architecture = 'x86_64'
	builder.compilation_options = ['-g', '-Wall', '-std=c11']
	builder.linker_options = [' -stdlib=libc++ -lc++abi']
	class << builder.compiler_data
		def default_include_paths(language)
			return @paths[language] if @paths[language]

			paths = []
			# Below is the recommended(!) way of getting standard search paths from GCC
			output = `echo | clang -v -x #{language} -E - 2>&1 1>/dev/null`
			collecting = false
			output.each_line do | line |
				case
				when line =~ /#include <\.\.\.> search starts here:/
					collecting = true
				when line =~ /End of search list\./
					collecting = false
				when line =~ / \(framework directory\)/
					# Skip frameworks
				else
					paths << line.strip if collecting
				end
			end
			@paths[language] = paths
		end
	end
end

# Rake::Builder.new do |builder|
# 	builder.target = 'library/libbanana.so'
# 	builder.programming_language = 'c++'
# 	builder.compiler = 'clang++'
# 	builder.linker = 'clang++'
# 	builder.source_search_paths = [ 'src' ]
# 	builder.objects_path = 'obj'
# 	builder.library_dependencies = ['glfw', 'GL', 'nanovg']
# 	builder.library_paths << 'library'
# 	builder.compilation_options = [ '-g', '-DDEBUG', '-std=c++11', '-Wall', '-DGLFW_INCLUDE_GLCOREARB', '-DGLCOREARB_PROTOTYPES', '-fPIC' ]
# 	builder.include_paths << 'nanovg/src'
# end

Rake::Builder.new do |builder|
	builder.target = 'banana'
	builder.target_type = :executable
	builder.programming_language = 'c++'
	builder.compiler = 'clang++'
	builder.linker = 'clang++'
	builder.architecture = 'x86_64'
	builder.source_search_paths = [ 'src' ]
	builder.objects_path = 'obj'
	builder.library_dependencies = ['glfw', 'GL', 'nanovg']
	builder.library_paths << 'library'
	builder.compilation_options = [ '-g', '-DDEBUG', '-std=c++11', '-Wall', '-DGLFW_INCLUDE_GLCOREARB', '-DGLCOREARB_PROTOTYPES' ]
	builder.linker_options = ['-stdlib=libc++ -nodefaultlibs -lc++ -lc++abi -lm -lc']
	# builder.compilation_options << '-march=native -mmmx -msse -msse2 -msse3'
	builder.include_paths << 'nanovg/src'
	
	class << builder.compiler_data
		def default_include_paths(language)
			return @paths[language] if @paths[language]

			paths = []
			# Below is the recommended(!) way of getting standard search paths from GCC
			output = `echo | clang -v -x #{language} -E - 2>&1 1>/dev/null`
			collecting = false
			output.each_line do | line |
				case
				when line =~ /#include <\.\.\.> search starts here:/
					collecting = true
				when line =~ /End of search list\./
					collecting = false
				when line =~ / \(framework directory\)/
					# Skip frameworks
				else
					paths << line.strip if collecting
				end
			end
			@paths[language] = paths
		end
	end
end