require 'securerandom'
require 'open3'
require 'fileutils'

helpers do
  def generator_run(spec)
    dir = SecureRandom.hex(3)
    dir = '/tmp/' + dir
    logger.info("Create Dir #{dir}")
    Dir.mkdir (dir)
    File.open(dir + '/default.in.spec', 'w') { |f| f.write(spec) }
    o, e, s = Open3.capture3("pwd")
    pwd = o.strip
    o, e, s = Open3.capture3("ln -s #{pwd}/bin/formatting #{dir}/formatting")
    o, e, s = Open3.capture3("ln -s #{pwd}/bin/src #{dir}/src")
    o, e, s = Open3.capture3('ls -l', chdir: dir, stdin_data: spec)
    logger.info("Running Formatter")
    o, e, s = Open3.capture3("./formatting -G #{dir}/generator.cpp", chdir: dir, stdin_data: spec)
    logger.info(o)
    logger.info("return status = #{s}")
    begin
      o = File.read("#{dir}/generator.cpp")
    rescue
      o = "syntax error"
    end

    FileUtils.rmdir dir
    return o
  end
end
