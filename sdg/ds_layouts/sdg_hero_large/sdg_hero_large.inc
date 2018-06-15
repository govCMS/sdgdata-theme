<?php
/**
 * @file
 * Layout for a hero large.
 */

/**
 * DS Implementation for hero large.
 */
function ds_sdg_hero_large() {
  return array(
    'label' => t('SDG: Hero Large'),
    'category' => t('SDG Custom'),
    'theme' => 'sdg_hero_large',
    'regions' => array(
      'image' => t('Image'),
      'main_content' => t('Content'),
    ),
    'css' => FALSE,
    'image' => FALSE,
  );
}
