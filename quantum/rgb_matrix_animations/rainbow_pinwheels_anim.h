#ifndef DISABLE_RGB_MATRIX_RAINBOW_PINWHEELS
RGB_MATRIX_EFFECT(PINWHEELS)
#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

bool PINWHEELS(effect_params_t* params) {
  RGB_MATRIX_USE_LIMITS(led_min, led_max);

  HSV hsv = { 0, rgb_matrix_config.sat, rgb_matrix_config.val };
  uint16_t time = scale16by8(g_rgb_counters.tick, rgb_matrix_config.speed / 4);
  int16_t cos_value = 3 * (cos8(time) - 128);
  int16_t sin_value = 3 * (sin8(time) - 128);
  for (uint8_t i = led_min; i < led_max; i++) {
    RGB_MATRIX_TEST_LED_FLAGS();
    hsv.h = ((g_led_config.point[i].y - k_rgb_matrix_center.y) * cos_value + (56 - abs8(g_led_config.point[i].x - k_rgb_matrix_center.x)) * sin_value) / 128 + rgb_matrix_config.hue;
    RGB rgb = hsv_to_rgb(hsv);
    rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
  }
  return led_max < DRIVER_LED_TOTAL;
}

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#endif // DISABLE_RGB_MATRIX_RAINBOW_PINWHEELS
