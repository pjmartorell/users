# frozen_string_literal: true

require 'json'

def each_step(json, type, &)
  json['workflows'].map { |w| w['steps'].select { |s| s['type'] == type.to_s } }.flatten.each(&)
end

def replace_oauth(app_json)
  client_id = ENV.fetch('CLIENT_ID', nil)
  client_secret = ENV.fetch('CLIENT_SECRET', nil)
  redirect_scheme = ENV.fetch('SCHEME', nil)

  each_step(app_json, :networkOAuth2) do |step|
    step['items'].each do |item|
      next unless item['oAuth2ClientId']

      item['oAuth2ClientId'] = client_id
      item['oAuth2ClientSecret'] = client_secret
      item['oAuth2RedirectScheme'] = redirect_scheme
    end
  end
end

def replace_servers(app_json)
  server_url = ENV.fetch('SERVER_URL', nil)

  app_json['servers'].each do |server|
    server['url'] = server_url
  end
end

desc 'Update app.json to use new env'
task env_set: :environment do
  project_name = ENV.fetch('PROJECT_NAME', nil)
  app_json_path = File.join(project_name, project_name, 'Resources', 'app.json')
  app_json = JSON.parse(File.read(app_json_path))
  replace_oauth(app_json)
  replace_servers(app_json)
  File.write(app_json_path, app_json.to_json)
end
