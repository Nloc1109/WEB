$(function () {
    $('#btnShowMenuMobile').click(function () {
        const target = $($(this).data('target'));
        target.toggleClass('active');
        target.find('.overlay-mb').one('click', function () {
            target.removeClass('active');
        })
    });

    $.fn.weekpicker = function (options) {

        // Variables
        var currentDate = options.defaultDate ? moment(options.defaultDate) : moment();

        // Private functions
        function getCurrentDate(element) {
            return element.data("DateTimePicker").date();
        }
        
        function setWeekYear(element, currentDate) {
            var firstDate = moment(currentDate).day(1).format(options.format);
            var lastDate = moment(currentDate).day(7).format(options.format);

            element.val(firstDate + ' - ' + lastDate);
        }

        return this.each(function () {
            // Append input field to weekpicker
            $(this).append("<input type='text' class='form-control text-center'>");

            var weekpickerDiv = $(this);
            var inputField = weekpickerDiv.find("input");

            // Append DateTimePicker to weekpicker's input field
            inputField.datetimepicker(options).on("dp.change", function (e) {
                // $(this) relates to inputField here
                var selectedDate = getCurrentDate($(this));
                setWeekYear($(this), selectedDate);

                var week = moment(selectedDate).isoWeek() + 1;
                var year = moment(selectedDate).year();

                weekpickerDiv.trigger('week_change', { week, year });
            }).on("dp.show", function () {
                var currentSelectedDate = getCurrentDate($(this));
                setWeekYear($(this), currentSelectedDate);
            }).on("dp.hide", function () {
                var currentSelectedDate = getCurrentDate($(this));
                setWeekYear($(this), currentSelectedDate);
            });
            // Set initial week & year
            setWeekYear(inputField, currentDate);
        });

    }

})