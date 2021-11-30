project('directory_explorer', 'cpp',
  version : '0.1.0',
  default_options : [
    'warning_level=3',
    'cpp_std=c++17',
  ])

threads_dep = dependency('threads')

executable('directory_explorer', 
  ['main.cpp', 'crawler.cpp'],
  dependencies : threads_dep,
  include_directories : '.')

# sudo apt install libgtest-dev
# if gtest is not installed, then meson will download it as subproject
gtest_dep = dependency('gtest', 
  main : true,
  fallback : ['gtest', 'gtest_main_dep']
)

crawler_tests = executable('tests', 
  ['tests/crawler_tests.cpp', 'crawler.cpp'],
  dependencies : [gtest_dep, threads_dep],
  include_directories : '.')

test('unit test', crawler_tests, workdir : meson.current_source_dir())
