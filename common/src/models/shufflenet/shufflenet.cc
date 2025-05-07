#include "models/shufflenet/shufflenet_v2.h"
#include <stdio.h>
#include "menu.h"
#include "models/shufflenet/shufflenet.h"
#include "models/shufflenet/input_image.h"
#include "tflite.h"

extern "C" {
#include "fb_util.h"
};

static void shufflenet_init(void) {
  tflite_load_model(shufflenet_v2 ,shufflenet_v2_len);
}

// Run classification, after input has been loaded
static int32_t shufflenet_classify() {
  printf("Running shufflenet\n");
  tflite_classify();

  // Process the inference results.
  int8_t* output = tflite_get_output();
  return (int32_t)output[1] - (int32_t)output[0];
}

static void do_classify_zeros() {
    tflite_set_input_zeros();
    int32_t result = shufflenet_classify();
    printf("Result after parameters with literal values is %ld\n", result);
}


static struct Menu MENU = {
    "Tests for shufflenet model",
    "shufflenet",
    {
      MENU_ITEM('z', "Run with zeros input", do_classify_zeros),
      MENU_END,
    },
};

void shufflenet_menu() {
  shufflenet_init();

#ifdef CSR_VIDEO_FRAMEBUFFER_BASE
  fb_init();
  flush_cpu_dcache();
  flush_l2_cache();
#endif

  menu_run(&MENU);  // Run the menu
}

