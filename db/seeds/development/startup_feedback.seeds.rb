require_relative 'helper'

after 'development:timeline_events', 'development:faculty' do
  puts 'Seeding startup_feedback'
  avengers = Startup.find_by(name: 'The Avengers')

  graded_event = TimelineEvent.joins(:timeline_event_grades).joins(:founders).where(founders: { id: avengers.founders.pluck(:id) }).last
  mickey = User.find_by(email: 'mickeymouse@example.com').faculty.first

  StartupFeedback.create!(
    feedback: Faker::Lorem.paragraphs(2).join("\n\n"),
    reference_url: "http://sv.localhost/startups/#{graded_event.startup.slug}#event-#{graded_event.id}",
    startup: avengers,
    faculty: mickey,
    activity_type: 'Feedback on presentation'
  )
end
