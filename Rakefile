require 'rake/clean'

CC = "g++"
SRCS = FileList["src/*.cpp"]
OBJS = SRCS.ext('o')

CLEAN.include(OBJS)
CLOBBER.include("jholiday")

task :default => "jholiday"

desc "Make jholiday"
file "jholiday" => OBJS do |t|
  sh "#{CC} -o #{t.name} #{t.prerequisites.join(' ')}"
end

desc "Complile all sources"
rule '.o' => ['.cpp'] do |t|
  sh "#{CC} -c #{t.source} -o #{t.name}"
end
