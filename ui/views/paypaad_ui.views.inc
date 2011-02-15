<?php
// $Id$

/**
 * @file
 * Implements Views module hooks.
 */

/**
 * Implements hook_views_data().
 */
function paypaad_ui_views_data() {
  $data = array();

  // Introducing {paypaad} table.
  $data['paypaad']['table']['group'] = t('Paypaad Transaction');

  $data['paypaad']['table']['base'] = array(
    'field' => 'pid',
    'title' => t('Paypaad Transaction'),
    'help' => t('Payment transactions information processed through Paypaad gateway.'),
  );

  $data['paypaad']['table']['join'] = array(
    'users' => array(
      'left_table' => 'users',
      'left_field' => 'uid',
      'field' => 'uid',
    ),
  );

  $data['paypaad']['pid'] = array(
    'title' => t('Paypaad transaction identifier'),
    'help'  => t('The Paypaad transaction ID.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
  );

  $data['paypaad']['uid'] = array(
    'title' => t('User'),
    'help'  => t('User ID of who the transaction performed by.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
    'relationship' => array(
      'handler' => 'views_handler_relationship',
      'base' => 'users',
      'base field' => 'uid',
      'label' => t('user'),
    ),
  );

  $data['paypaad']['transaction_reference_id'] = array(
    'title' => t('Paypaad transaction reference identifier'),
    'help' => t('Reference ID of transaction, also known as tref in Paypaad talk.'),
    'field' => array(
      'handler' => 'views_handler_field_xss',
      'click sortable' => TRUE,
     ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  $data['paypaad']['invoice_number'] = array(
    'title' => t('Paypaad invoice number'),
    'help' => t('Paypaad transaction invoice number as returned by the gateway.'),
    'field' => array(
      'handler' => 'views_handler_field_xss',
      'click sortable' => TRUE,
     ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  $data['paypaad']['invoice_date'] = array(
    'title' => t('Paypaad invoice date'),
    'help' => t('Paypaad transaction invoice date as returned by the gateway.'),
    'field' => array(
      'handler' => 'views_handler_field_xss',
      'click sortable' => TRUE,
     ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  $data['paypaad']['trace_number'] = array(
    'title' => t('Paypaad trace number'),
    'help' => t('Paypaad transaction trace number as returned by the gateway.'),
    'field' => array(
      'handler' => 'views_handler_field_xss',
      'click sortable' => TRUE,
     ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  $data['paypaad']['reference_number'] = array(
    'title' => t('Paypaad reference number'),
    'help' => t('Paypaad transaction reference number as returned by the gateway.'),
    'field' => array(
      'handler' => 'views_handler_field_xss',
      'click sortable' => TRUE,
     ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  $data['paypaad']['transaction_date'] = array(
    'title' => t('Paypaad transaction date'),
    'help' => t('Paypaad transaction date as returned by the gateway.'),
    'field' => array(
      'handler' => 'views_handler_field_xss',
      'click sortable' => TRUE,
     ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  $data['paypaad']['amount'] = array(
    'title' => t('Paypaad transaction amount'),
    'help' => t('Transaction amount paid by the customer.'),
    'field' => array(
      'handler' => 'views_handler_field_xss',
      'click sortable' => TRUE,
     ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  $data['paypaad']['module_id'] = array(
    'title' => t('Paypaad module identifier'),
    'help' => t('Payment handler module ID.'),
    'field' => array(
      'handler' => 'views_handler_field_xss',
      'click sortable' => TRUE,
     ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  $data['paypaad']['entity_id'] = array(
    'title' => t('Paypaad entity identifier'),
    'help' => t('Drupal entity ID, might be a node, UC order, etc.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
  );

  return $data;
}

