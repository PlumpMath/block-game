file(READ ${CMAKE_ARGV1}/${CMAKE_ARGV3} STRING)
string(REGEX REPLACE ";" "\\\\;" STRING "${STRING}")
file(WRITE ${CMAKE_ARGV2}/${CMAKE_ARGV3}.txt R\"\(${STRING}\)\")