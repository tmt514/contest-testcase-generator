require 'sinatra'
require 'slim'
require 'compass'

# set logger
use Rack::Logger
helpers do 
  def logger
    request.logger
  end
end

# Internet connection settings
set :bind, '0.0.0.0'
set :port, 4567

# set Version number
set :version, 'v0.0.1'

# set compass
configure do
  set :scss, {style: :compact, debug_info: false}
end


get '/css/:name.css' do
    content_type 'text/css', :charset => 'utf-8'
      scss :"css/#{params[:name]}", Compass.sass_engine_options
end




require_relative 'utils/generator_runner'

get '/hi' do
  @spec = "a, b: integer\n###\na b\n###\n"
  @gencode = generator_run(@spec)
  slim :spec_submit, layout: :layout_spec
end

post '/hi' do
  @spec = params[:spec]
  @spec = @spec + "\n"
  @spec.each_byte do |i|
    puts i
  end
  puts @spec
  @gencode = generator_run(@spec)
  slim :spec_submit, layout: :layout_spec
end
