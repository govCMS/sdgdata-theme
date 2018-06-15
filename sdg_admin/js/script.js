/**
 * @file
 * A JavaScript file for the admin theme.
 */
(function ($, Drupal, window, document, undefined) {

  /*
   * Export table as CSV.
   */
  Drupal.behaviors.inputFilterDescToggle = {
    attach: function (context, settings) {

      // Ability to export views tables as a CSV.
      $('.views-csv-export')
        .find('.view-content .views-table:first').attr('id', 'views-table-first').end()
        .prepend('<a href="#" download="' + $(document).find('title').text() + '.csv" onclick="return ExcellentExport.csv(this, \'views-table-first\')">Download CSV</a>')
    }
  };

})(jQuery, Drupal, this, this.document);