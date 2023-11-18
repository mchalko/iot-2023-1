% rebase('base.tpl', nav='data')
% import db_interface as db

% entries_count = 15

<div class="container mt-3"> 

    <table class="table table-striped rounded-3 overflow-hidden">
        <caption>The table is showing last {{entries_count}} entries</caption>
        <thead class="table-dark">
          <tr>
            <th scope="col">Insertion time</th>
            <th scope="col">Temperature</th>
            <th scope="col">Pressure</th>
            <th scope="col">Light Intensity</th>
          </tr>
        </thead>
        <tbody>
            % for time, vals in db.get_last_all(entries_count).items():
            <tr>
                <th scope="row">{{time}}</td>
                <td>{{vals["temperature"]}}</td>
                <td>{{vals["pressure"]}}</td>
                <td>{{vals["light"]}}</td>
            </tr>
            % end 
        </tbody>
      </table>

</div>