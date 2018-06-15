<?php

/**
 * @file
 * Default theme implementation to display a block.
 */
?>
<div class="view-indicator-search-form no-constraints">
  <div class="views-filters-toggle" data-search-filters-toggle="1">
    <?php print t('Filter by'); ?>
  </div>
  <div class="views-filters-container" data-search-filters-container="1">
    <div class="views-filters-close" data-search-filters-close="1"></div>
    <div class="views-filters">
      <?php print $content ?>
    </div>
  </div>
</div>
