require 'rubygems' if RUBY_VERSION < '1.9'
require 'rake/builder'

Rake::Builder.new do |builder|
	builder.target = 'library/libnanovg.a'
	builder.target_type = :static_library
	builder.programming_language = 'c'
	builder.source_search_paths = ['nanovg/src']
	builder.objects_path = 'nanovg'
	builder.include_paths = ['nanovg/src']
	builder.compilation_options = ['-g'
]end

Rake::Builder.new do |builder|
	builder.target = 'banana'
	builder.target_type = :executable
	builder.programming_language = 'c++'
	builder.compiler = 'clang++'
	builder.linker = 'clang++'
	builder.source_search_paths = [ 'src' ]
	builder.objects_path = 'obj'
	builder.library_dependencies = ['glfw', 'GL', 'nanovg']
	builder.library_paths << 'library'
	builder.compilation_options = [ '-g', '-DDEBUG', '-std=c++11', '-Wall', '-DGLFW_INCLUDE_GLCOREARB', '-DGLCOREARB_PROTOTYPES' ]
	builder.include_paths << 'nanovg/src'
end