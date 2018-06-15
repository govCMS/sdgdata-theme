<?php

/**
 * @file
 * Preprocessors for html.
 */

/**
 * Implements template_preprocess_html().
 */
function sdg_preprocess_html(&$vars) {
  // Add Cookie Info <script> tag.
  sdg_metatag_add_cookieinfo();

  // Add RSS Feed <link> tag.
  sdg_metatag_add_rss_link();
}
