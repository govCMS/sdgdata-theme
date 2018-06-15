<?php
/**
 * @file
 *
 * Preprocess breadcrumb.
 */

/**
 * Implements hook_preprocess_breadcrumb().
 *
 * Wrap each crumb.
 */
function sdg_preprocess_breadcrumb(&$variables) {
  if (!empty($variables['breadcrumb'])) {
    foreach ($variables['breadcrumb'] as &$crumb) {
      $crumb = '<span class="crumb">' . $crumb . '</span>';
    }
  }
}