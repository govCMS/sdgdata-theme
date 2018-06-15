<?php

/**
 * @file
 * Text helpers.
 */

/**
 * Helper function for nice text trimming.
 *
 * Uses views_trim_text() with sensible defaults if available and falls back
 * to text_summary().
 *
 * @param string $text
 *   The text to trim.
 * @param int $length
 *   The maximum length.
 *
 * @return string
 *   The trimmed text.
 */
function sdg_text_trim($text, $length = 300) {
  if (function_exists('views_trim_text')) {
    $options = array(
      'max_length' => $length,
      'ellipsis' => TRUE,
      'word_boundary' => TRUE,
      'html' => TRUE,
    );
    $trimmed_text = views_trim_text($options, $text);
  }
  else {
    $trimmed_text = text_summary($text, 'rich_text', $length);
  }

  return $trimmed_text;
}

/**
 * Strip tags from a text field.
 *
 * This ensures that the string has been completely decoded before stripping
 * the tags.
 *
 * @param string $string
 *   A string the strip tags from.
 * @param string $allowed_tags
 *   A tag list as expected by strip_tags.
 *
 * @return string
 *   A string value with tags removed.
 */
function sdg_strip_tags($string, $allowed_tags = '<strong>') {
  return strip_tags(htmlspecialchars_decode($string), $allowed_tags);
}
