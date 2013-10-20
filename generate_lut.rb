def get_ideal_speed(setting)
  MAX_SETTING = 127.0
  MAX_SPEED = 100.0
  (MAX_SPEED / MAX_SETTING) * (setting - MAX_SETTING) + MAX_SPEED
end

def make_setting_lut(actual_speeds)
  lut = Array.new(128)

  actual_speeds.each_with_index { |setting, actual_speed|
    least_diff = 1000000
    best_match = 0

    actual_speeds.each_with_index { |setting, actual_speed|
      ideal_speed = get_ideal_speed(setting)
      diff = (ideal_speed - actual_speed).abs

      if (diff < least_diff)
        best_match = setting
        least_diff = diff
      end
    }

    lut[setting] = best_match
  }

  lut
end
