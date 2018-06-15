<?php

/**
 * @file
 * Preprocessors for page.
 */

/**
 * Implements template_preprocess_page.
 */
function sdg_preprocess_page(&$variables) {
  $theme_path = path_to_theme();
  $site_logo_path = $theme_path . '/logo.svg';
  $footer_logo = $theme_path . '/images/australian-government-logo.svg';

  // Override $logo variable to render SVG.
  if (file_exists($site_logo_path)) {
    $variables['logo'] = file_create_url($site_logo_path);
  }

  // Render Government logo in footer.
  if (file_exists($footer_logo)) {
    $variables['footer_logo'] = file_create_url($footer_logo);
  }

  // Explicitly hide the title as almost every page has a hero. If a page
  // requires a title it can conditionally reverse this.
  $variables['title'] = FALSE;

  // RSS URL.
  $variables['rss_url'] = url('rss');
  if ($goal_tid = sdg_term_get_goal_tid_for_current_page()) {
    $variables['rss_url'] .= '/' . $goal_tid;
  }
}
