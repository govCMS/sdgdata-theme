<?php
// $Id$

/**
 * @file
 * Generates the markup required to output indicator status.
 *
 * Available variables:
 * - $indicator_background: Indicator background colour to be displayed.
 * - $indicator_status: Indicator status text to be displayed.
 */
?>

<div class="node-indicator__status">
  <a href="<?php print $link; ?>" class="node-indicator__status-link <?php print $background_class; ?>" title="Show all: <?php print $title; ?>">
    <?php print $title; ?>
  </a>
</div>
