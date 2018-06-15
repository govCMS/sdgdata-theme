<?php
/**
 * @file
 * Layout for a hero large.
 */

/**
 * DS Implementation for hero default.
 */
function ds_sdg_hero_default() {
  return array(
    'label' => t('SDG: Hero Default'),
    'category' => t('SDG Custom'),
    'theme' => 'sdg_hero_default',
    'regions' => array(
      'image' => t('Image'),
      'main_content' => t('Content'),
    ),
    'css' => FALSE,
    'image' => FALSE,
  );
}
