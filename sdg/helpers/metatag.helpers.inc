<?php

/**
 * @file
 * Includes metatag helpers.
 */

/**
 * Adds the Cookie Info Script tag to the <head> of the page.
 */
function sdg_metatag_add_cookieinfo() {
  // Continue only if user is on the home page.
  if (!drupal_is_front_page()) {
    return;
  }

  // Pass ID & parameters through to script.
  $cookieinfo = array(
    '#tag' => 'script',
    '#type' => 'html_tag',
    '#value' => '',
    '#attributes' => array(
      'src' => 'https://cookieinfoscript.com/js/cookieinfo.min.js',
      'type' => 'text/javascript',
      'id' => 'cookieinfo',
      'data-position' => 'bottom',
      'data-text-align' => 'left',
      'data-message' => 'Our website uses cookies so that we can provide you with the best user experience. For more information view our ',
      'data-linkmsg' => 'Privacy and Cookies Policy.',
      'data-divlinkbg' => 'none',
      'data-bg' => '#19486A',
      'data-link' => '#fff',
      'data-fg' => '#fff',
    ),
  );

  // Add cookie info script to head.
  drupal_add_html_head($cookieinfo, 'cookieinfo');
}

/**
 * Adds the RSS feed link to the <head> of the page.
 */
function sdg_metatag_add_rss_link() {
  $data = array(
    '#tag' => 'link',
    '#type' => 'html_tag',
    '#attributes' => array(
      'rel' => 'alternate',
      'type' => 'application/rss+xml',
      'title' => t('@site_name RSS Feed', array(
        '@site_name' => variable_get('site_name', ''),
      )),
      'href' => url('rss', array(
        'absolute' => TRUE,
      )),
    ),
  );

  drupal_add_html_head($data, 'rss_feed');
}
